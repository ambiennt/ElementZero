#pragma once

#include "../dll.h"
#include "ActorDefinitionIdentifier.h"

#include <unordered_map>
#include <cstdint>
#include <string>

struct ActorInfo {
    uint32_t mRuntimeId; // 0x0
    ActorDefinitionIdentifier mIdentifier, mBaseIdentifier; // 0x8, 0xB0
    bool mHasSpawnEgg, mIsSummonable, mIsExperimental; // 0x158, 0x159, 0x15A
};
static_assert(sizeof(ActorInfo) == 0x160);

class ActorInfoRegistry {
public:
    std::unordered_map<uint64_t, uint32_t> mActorInfoNameMap; // 0x0
    std::unordered_map<uint32_t, ActorInfo> mActorInfoMap; // 0x40
    uint32_t mLastId; // 0x80

    // return value of this is the minecraft:spawn_egg's aux value
    // pass in ActorDefinitionIdentifier.getCanonicalName() or namespaced entity name (e.g. "minecraft:creeper")
    MCAPI uint32_t getActorInfoId(const std::string& canonicalName) const;
};
static_assert(sizeof(ActorInfoRegistry) == 0x88);