#pragma once

#include "../Actor/ActorUniqueID.h"
#include "../dll.h"

struct ActorBlockSyncMessage {
	ActorUniqueID mEntityUniqueID;
	int8_t mMessage[4];
};

static_assert(sizeof(ActorBlockSyncMessage) == 0x10);