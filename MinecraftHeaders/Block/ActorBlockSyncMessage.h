#pragma once

#include "../Actor/ActorUniqueID.h"
#include "../dll.h"

struct ActorBlockSyncMessage {
	ActorUniqueID id;
	char unknown[0x4];
};

static_assert(sizeof(ActorBlockSyncMessage) == 0x10);