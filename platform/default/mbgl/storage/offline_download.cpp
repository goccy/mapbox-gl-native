#include <mbgl/storage/offline_download.hpp>
#include <mbgl/storage/offline_database.hpp>
#include <mbgl/storage/file_source.hpp>
#include <mbgl/storage/resource.hpp>
#include <mbgl/storage/response.hpp>
#include <mbgl/style/style_parser.hpp>
#include <mbgl/layer/symbol_layer.hpp>
#include <mbgl/text/glyph.hpp>
#include <mbgl/util/tile_cover.hpp>

#include <set>

namespace mbgl {

OfflineDownload::OfflineDownload(int64_t id_,
                                 OfflineRegionDefinition&& definition_,
                                 OfflineDatabase& offlineDatabase_,
                                 FileSource& onlineFileSource_)
    : id(id_),
      definition(definition_),
      offlineDatabase(offlineDatabase_),
      onlineFileSource(onlineFileSource_) {
}

OfflineDownload::~OfflineDownload() = default;

void OfflineDownload::setObserver(std::unique_ptr<OfflineRegionObserver> observer_) {
    observer = std::move(observer_);
}

void OfflineDownload::setState(OfflineRegionDownloadState state) {
    if (status.downloadState == state) {
        return;
    }

    status.downloadState = state;

    if (status.downloadState == OfflineRegionDownloadState::Active) {
        activateDownload();
    } else {
        deactivateDownload();
    }
}

std::vector<Resource> OfflineDownload::spriteResources(const StyleParser& parser) const {
    std::vector<Resource> result;

    if (!parser.spriteURL.empty()) {
        result.push_back(Resource::spriteImage(parser.spriteURL, definition.pixelRatio));
        result.push_back(Resource::spriteJSON(parser.spriteURL, definition.pixelRatio));
    }

    return result;
}

std::vector<Resource> OfflineDownload::glyphResources(const StyleParser& parser) const {
    std::vector<Resource> result;

    if (!parser.glyphURL.empty()) {
        for (const auto& fontStack : parser.fontStacks()) {
            for (uint32_t i = 0; i < 256; i++) {
                result.push_back(Resource::glyphs(parser.glyphURL, fontStack, getGlyphRange(i * 256)));
            }
        }
    }

    return result;
}

std::vector<Resource> OfflineDownload::tileResources(SourceType type, uint16_t tileSize, const SourceInfo& info) const {
    std::vector<Resource> result;

    for (const auto& tile : definition.tileCover(type, tileSize, info)) {
        result.push_back(Resource::tile(info.tiles[0], definition.pixelRatio, tile.x, tile.y, tile.z));
    }

    return result;
}

OfflineRegionStatus OfflineDownload::getStatus() const {
    OfflineRegionStatus result;
    result.requiredResourceCount++;

    optional<Response> styleResponse = offlineDatabase.get(Resource::style(definition.styleURL));
    if (!styleResponse) {
        return result;
    }

    result.completedResourceCount += 1;
    result.completedResourceSize += styleResponse->data->length();

    StyleParser parser;
    parser.parse(*styleResponse->data);

    result.requiredResourceCount += spriteResources(parser).size();
    result.requiredResourceCount += glyphResources(parser).size();

    for (const auto& source : parser.sources) {
        switch (source->type) {
        case SourceType::Vector:
        case SourceType::Raster:
            if (source->getInfo()) {
                result.requiredResourceCount += tileResources(source->type, source->tileSize, *source->getInfo()).size();
            } else {
                result.requiredResourceCount += 1;
                optional<Response> sourceResponse = offlineDatabase.get(Resource::source(source->url));
                if (sourceResponse) {
                    result.completedResourceCount += 1;
                    result.completedResourceSize += sourceResponse->data->length();
                    result.requiredResourceCount += tileResources(source->type, source->tileSize,
                        *StyleParser::parseTileJSON(*sourceResponse->data, source->url, source->type)).size();
                }
            }
            break;

        case SourceType::GeoJSON:
            if (!source->url.empty()) {
                result.requiredResourceCount += 1;
            }
            break;

        case SourceType::Video:
        case SourceType::Annotations:
            break;
        }
    }

    return result;
}

void OfflineDownload::activateDownload() {
    ensureResource(Resource::style(definition.styleURL), [&] (Response styleResponse) {
        StyleParser parser;
        parser.parse(*styleResponse.data);

        for (const auto& resource : spriteResources(parser)) {
            ensureResource(resource);
        }

        for (const auto& resource : glyphResources(parser)) {
            ensureResource(resource);
        }

        for (const auto& source : parser.sources) {
            switch (source->type) {
            case SourceType::Vector:
            case SourceType::Raster:
                ensureTileJSON(*source, [=] (const std::vector<Resource>& tileResources_) {
                    for (const auto& resource : tileResources_) {
                        ensureResource(resource);
                    }
                });
                break;

            case SourceType::GeoJSON:
                if (!source->url.empty()) {
                    ensureResource(Resource::source(source->url));
                }
                break;

            case SourceType::Video:
            case SourceType::Annotations:
                break;
            }
        }
    });
}

void OfflineDownload::deactivateDownload() {
    requests.clear();
}

void OfflineDownload::ensureTileJSON(const Source& source, std::function<void (const std::vector<Resource>&)> callback) {
    SourceType type = source.type;
    uint16_t tileSize = source.tileSize;
    std::string url = source.url;

    if (source.getInfo()) {
        callback(tileResources(type, tileSize, *source.getInfo()));
    } else {
        ensureResource(Resource::source(url), [=] (Response sourceResponse) {
            callback(tileResources(type, tileSize, *StyleParser::parseTileJSON(*sourceResponse.data, url, type)));
        });
    }
}

void OfflineDownload::ensureResource(const Resource& resource, std::function<void (Response)> callback) {
    status.requiredResourceCount++;
    notifyObserver();

    optional<Response> offlineResponse = offlineDatabase.getRegionResource(id, resource);

    if (offlineResponse) {
        if (callback) {
            callback(*offlineResponse);
        }

        status.completedResourceCount++;
        if (offlineResponse->data) {
            status.completedResourceSize += offlineResponse->data->length();
        }

        notifyObserver();

        return;
    }

    auto it = requests.insert(requests.begin(), nullptr);
    *it = onlineFileSource.request(resource, [=] (Response onlineResponse) {
        requests.erase(it);

        if (onlineResponse.error) {
            return;
        }

        offlineDatabase.putRegionResource(id, resource, onlineResponse);
        if (callback) {
            callback(onlineResponse);
        }

        status.completedResourceCount++;
        if (onlineResponse.data) {
            status.completedResourceSize += onlineResponse.data->length();
        }

        notifyObserver();
    });
}

void OfflineDownload::notifyObserver() {
    if (observer) {
        observer->statusChanged(status);
    }
}

} // namespace mbgl
