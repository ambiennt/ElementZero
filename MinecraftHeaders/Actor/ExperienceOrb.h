#pragma once

#include <modutils.h>
#include "Actor.h"
#include "ActorUniqueID.h"

#include "../dll.h"

class ExperienceOrb : public Actor {
public:

	enum class DropType : int8_t {
		NoType = 0x0,
		FromBlock = 0x1,
		FromMob = 0x2,
		FromPlayer = 0x3,
	};

	BUILD_ACCESS_MUT(ActorUniqueID, mFollowingPlayer, 0x620);
	BUILD_ACCESS_MUT(int32_t, mFollowingTime, 0x628);
	BUILD_ACCESS_MUT(int32_t, mAge, 0x62C);
	BUILD_ACCESS_MUT(int32_t, mHealth, 0x630);

	// reference: Mob::TickDeath
	MCAPI static void spawnOrbs(class BlockSource &region, class Vec3 const &pos, int32_t xpValue, DropType type, Player *owner);
};

