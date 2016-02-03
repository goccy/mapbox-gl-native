#ifndef MBGL_OFFLINE_DATABASE
#define MBGL_OFFLINE_DATABASE

#include <mbgl/storage/resource.hpp>
#include <mbgl/storage/offline.hpp>
#include <mbgl/util/noncopyable.hpp>
#include <mbgl/util/optional.hpp>

#include <unordered_map>
#include <memory>
#include <string>

namespace mapbox {
namespace sqlite {
class Database;
class Statement;
}
}

namespace mbgl {

class Response;
class TileID;

class OfflineDatabase : private util::noncopyable {
public:
    OfflineDatabase(const std::string& path);
    ~OfflineDatabase();

    optional<Response> get(const Resource&);
    void put(const Resource&, const Response&);

    std::vector<OfflineRegion> listRegions();

    OfflineRegion createRegion(const OfflineRegionDefinition&,
                               const OfflineRegionMetadata&);

    void deleteRegion(OfflineRegion&&);

    optional<Response> getRegionResource(int64_t regionID, const Resource&);
    void putRegionResource(int64_t regionID, const Resource&, const Response&);

    OfflineRegionDefinition getRegionDefinition(int64_t regionID);

private:
    void ensureSchema();
    void removeExisting();
    mapbox::sqlite::Statement& getStatement(const char *);

    optional<Response> getTile(const Resource::TileData&);
    void putTile(const Resource::TileData&, const Response&);

    optional<Response> getResource(const Resource&);
    void putResource(const Resource&, const Response&);

    void markUsed(int64_t regionID, const Resource&);

    const std::string path;
    std::unique_ptr<::mapbox::sqlite::Database> db;
    std::unordered_map<const char *, std::unique_ptr<::mapbox::sqlite::Statement>> statements;
};

} // namespace mbgl

#endif
