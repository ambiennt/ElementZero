#pragma once

#include "../dll.h"
#include "../Actor/ActorUniqueID.h"
#include "../Math/BlockPos.h"
#include "../Container/ContainerType.h"

#include <variant>

class Actor;
class Player;

class ContainerScreenContext {
public:
	Player *mPlayer; // 0x0
	ContainerType mScreenContainerType; // 0x8
	std::variant<std::monostate, ActorUniqueID, BlockPos> mOwner; // 0x10

	MCAPI Actor* tryGetActor();
};

static_assert(sizeof(ContainerScreenContext) == 0x28);