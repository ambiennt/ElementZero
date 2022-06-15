#pragma once

#include "../dll.h"
#include <string>
#include <memory>
#include <atomic>

class AsynchronousIPResolver {
public:

    struct ResolvedIp {
        std::string mIp;
        std::atomic<bool> mReady;
    };

    std::string mUrl;
    std::shared_ptr<AsynchronousIPResolver::ResolvedIp> mResolvedIpPtr;
};

static_assert(sizeof(AsynchronousIPResolver) == 0x30);