#pragma once

#include "../Actor/ActorUniqueID.h"
#include "../dll.h"

struct ActorBlockSyncMessage {

	enum class MessageId : int32_t {
		NONE = 0x0,
		CREATE = 0x1,
		DESTROY = 0x2,
	};

	ActorUniqueID mEntityUniqueID; // 0x0
	ActorBlockSyncMessage::MessageId mMessage; // 0x8
};

static_assert(sizeof(ActorBlockSyncMessage) == 0x10);