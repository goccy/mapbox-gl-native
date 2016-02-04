#include <mbgl/util/clip_id.hpp>

#include <mbgl/platform/log.hpp>
#include <mbgl/util/math.hpp>
#include <mbgl/util/std.hpp>
#include <mbgl/map/tile.hpp>

#include <list>
#include <vector>
#include <bitset>
#include <cassert>
#include <iostream>
#include <algorithm>

namespace mbgl {

ClipIDGenerator::Leaf::Leaf(Tile &tile_) : tile(tile_) {}

void ClipIDGenerator::Leaf::add(const TileID &p) {
    if (p.isChildOf(tile.id)) {
        // Ensure that no already present child is a parent of the new p.
        for (const auto& child : children) {
            if (p.isChildOf(child))
                return;
        }
        children.push_front(p);
    }
}

bool ClipIDGenerator::Leaf::operator==(const Leaf &other) const {
    return tile.id == other.tile.id && children == other.children;
}



using Iterator = std::forward_list<Tile*>::const_iterator;

inline Iterator lower_bound(const Iterator& begin, const Iterator& end, const TileID& id) {
    for (auto lower = begin; lower != end; ++lower) {
        if (!((*lower)->id < id)) {
            return lower;
        }
    }
    return end;
}

bool coveredByChildren(const Iterator begin, const Iterator end) {
    for (const auto& child : (*begin)->id.children()) {
        const auto lower = lower_bound(begin, end, child);
        if (lower == end || ((*lower)->id != child && !coveredByChildren(lower, end))) {
            return false;
        }
    }

    // We looked at all four immediate children and verified that they're covered.
    return true;
}

void ClipIDGenerator::update(std::forward_list<Tile*> tiles) {
    util::erase_after_if(tiles, [](auto t) { return t == nullptr; });
    tiles.sort([](const Tile* a, const Tile* b) { return a->id < b->id; });

    // Remove parents from the list that are entirely covered by their children.
    for (auto it = tiles.before_begin(), next = it;
         it != tiles.end() && (next = std::next(it)) != tiles.end(); ++it) {
        if (coveredByChildren(next, tiles.end())) {
            tiles.erase_after(it);
        }
    }

    std::size_t size = 0;

    const auto end = tiles.end();
    for (auto it = tiles.begin(); it != end; it++) {
        Tile& tile = **it;
        Leaf leaf{ tile };

        // Try to add all remaining ids as children. We sorted the tile list
        // by z earlier, so all preceding items cannot be children of the current
        // tile.
        for (auto child_it = std::next(it); child_it != end; child_it++) {
            leaf.add((*child_it)->id);
        }
        leaf.children.sort();

        // Loop through all existing pools and try to find a matching ClipID.
        auto existing = std::find(pool.begin(), pool.end(), leaf);
        if (existing != pool.end()) {
            leaf.tile.clip = existing->tile.clip;
        } else {
            // We haven't found an existing clip ID
            leaf.tile.clip = {};
            size++;
        }

        pool.emplace_back(std::move(leaf));
    }

    if (size > 0) {
        const uint32_t bit_count = util::ceil_log2(size + 1);
        const std::bitset<8> mask = uint64_t(((1ul << bit_count) - 1) << bit_offset);

        // We are starting our count with 1 since we need at least 1 bit set to distinguish between
        // areas without any tiles whatsoever and the current area.
        uint8_t count = 1;
        for (auto& tile : tiles) {
            tile->clip.mask |= mask;

            // Assign only to clip IDs that have no value yet.
            if (tile->clip.reference.none()) {
                tile->clip.reference = uint32_t(count++) << bit_offset;
            }
        }

        bit_offset += bit_count;
    }

    if (bit_offset > 8) {
        Log::Error(Event::OpenGL, "stencil mask overflow");
    }
}

template <typename Container>
bool coveredByChildren(const TileID& id, const Container& container) {
    for (const auto& child : id.children()) {
        const auto lower = container.lower_bound(child);
        if (lower == container.end() ||
            (lower->first != child && !coveredByChildren(child, container))) {
            return false;
        }
    }

    // We looked at all four immediate children and verified that they're covered.
    return true;
}

std::map<TileID, ClipID> ClipIDGenerator::getStencils() const {
    std::map<TileID, ClipID> stencils;

    // Merge everything.
    for (auto& leaf : pool) {
        auto res = stencils.emplace(leaf.tile.id, leaf.tile.clip);
        if (!res.second) {
            // Merge with the existing ClipID when there was already an element with the
            // same tile ID.
            res.first->second |= leaf.tile.clip;
        }
    }

    for (auto it = stencils.begin(); it != stencils.end(); ++it) {
        auto& childId = it->first;
        auto& childClip = it->second;

        // Loop through all preceding stencils, and find all parents.
        for (auto parentIt = std::make_reverse_iterator(it); parentIt != stencils.rend();
             ++parentIt) {
            auto& parentId = parentIt->first;
            if (childId.isChildOf(parentId)) {
                // Once we have a parent, we add the bits  that this ID hasn't set yet.
                const auto& parentClip = parentIt->second;
                const auto mask = ~(childClip.mask & parentClip.mask);
                childClip.reference |= mask & parentClip.reference;
                childClip.mask |= parentClip.mask;
            }
        }
    }

    // Remove tiles that are entirely covered by children.
    util::erase_if(stencils, [&] (const auto& stencil) {
        return coveredByChildren(stencil.first, stencils);
    });

    return stencils;
}

} // namespace mbgl
