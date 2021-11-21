#pragma once

#include "../dll.h"
#include "../Actor/Player.h"
#include "../Actor/ActorUniqueID.h"
#include "../Math/BlockPos.h"
#include "../Container/ContainerType.h"

#include <variant>

class ContainerScreenContext {
	Player *mPlayer;
	ContainerType mScreenContainerType;
	std::variant<std::monostate, ActorUniqueID, BlockPos> mOwner;

	MCAPI Actor* tryGetActor(void);
};