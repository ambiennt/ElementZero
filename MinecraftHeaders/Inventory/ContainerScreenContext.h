#pragma once

#include "../dll.h"
#include "../Actor/Player.h"
#include "../Actor/ActorUniqueID.h"
#include "../Math/BlockPos.h"
#include "../Container/ContainerType.h"

#include <variant>

class ContainerScreenContext {
public:
	Player *mPlayer; // 0x0
	ContainerType mScreenContainerType; // 0x8
	std::variant<std::monostate, ActorUniqueID, BlockPos> mOwner; // 0x10

	MCAPI Actor* tryGetActor(void);
};

static_assert(offsetof(ContainerScreenContext, mPlayer) == 0x0);
static_assert(offsetof(ContainerScreenContext, mScreenContainerType) == 0x8);
static_assert(offsetof(ContainerScreenContext, mOwner) == 0x10);
static_assert(sizeof(ContainerScreenContext) == 0x28);