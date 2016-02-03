#pragma once

#include <mbgl/storage/offline.hpp>
#include <mbgl/style/types.hpp>

#include <list>
#include <memory>

namespace mbgl {

class OfflineDatabase;
class FileSource;
class FileRequest;
class Resource;
class Response;
class SourceInfo;
class StyleParser;
class Source;

/**
 * Coordinates the request and storage of all resources for an offline region.

 * @private
 */
class OfflineDownload {
public:
    OfflineDownload(int64_t id, OfflineRegionDefinition&&, OfflineDatabase& offline, FileSource& online);
    ~OfflineDownload();

    void setObserver(std::unique_ptr<OfflineRegionObserver>);
    void setState(OfflineRegionDownloadState);

    OfflineRegionStatus getStatus() const;

private:
    void activateDownload();
    void deactivateDownload();
    void notifyObserver();

    std::vector<Resource> spriteResources(const StyleParser&) const;
    std::vector<Resource> glyphResources(const StyleParser&) const;
    std::vector<Resource> tileResources(SourceType, uint16_t, const SourceInfo&) const;

    /*
     * Recursive async function that iterates over sources, accumulates required resource
     * counts in status, and calls the callback when all sources have been (asynchronously)
     * checked.
     */
    void getTileStatus(OfflineRegionStatus,
                       std::vector<std::unique_ptr<Source>>,
                       std::function<void (std::exception_ptr, optional<OfflineRegionStatus>)>) const;

    /*
     * Ensure that the resource is stored in the database, requesting it if necessary.
     * While the request is in progress, it is recorded in `requests`. If the download
     * is deactivated, all in progress requests are cancelled.
     */
    void ensureResource(const Resource&, std::function<void (Response)> = {});

    void tryTileJSON(const Source&, std::function<void (const std::vector<Resource>&)>);
    void ensureTileJSON(const Source&, std::function<void (const std::vector<Resource>&)>);

    int64_t id;
    OfflineRegionDefinition definition;
    OfflineDatabase& offlineDatabase;
    FileSource& onlineFileSource;
    OfflineRegionStatus status;
    std::unique_ptr<OfflineRegionObserver> observer;
    std::list<std::unique_ptr<FileRequest>> requests;
};

} // namespace mbgl
