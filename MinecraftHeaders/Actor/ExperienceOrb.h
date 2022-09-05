#pragma once

#include <modutils.h>
#include "Actor.h"

#include "../dll.h"

class BlockSource;
class Vec3;
class Player;
struct ActorUniqueID;

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

	// xref: Mob::TickDeath
	MCAPI static void spawnOrbs(BlockSource &region, const Vec3 &pos, int32_t xpValue, DropType type, Player *owner);
};