#pragma once

#include "CommandOrigin.h"
#include "../Actor/ActorUniqueID.h"
#include "../Core/mce.h"

struct CommandOriginData {
	CommandOriginType mType; // 0x0
	mce::UUID mUUID; // 0x8
	std::string mRequestId; // 0x18
	ActorUniqueID mPlayerId; // 0x38 (shows as int64 in IDA?)
};

static_assert(offsetof(CommandOriginData, mUUID) == 0x8);
static_assert(offsetof(CommandOriginData, mRequestId) == 0x18);
static_assert(offsetof(CommandOriginData, mPlayerId) == 0x38);
static_assert(sizeof(CommandOriginData) == 0x40);