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

	CLASS_FIELD(mFollowingPlayer, 0x620, ActorUniqueID);
	CLASS_FIELD(mFollowingTime, 0x628, int32_t);
	CLASS_FIELD(mAge, 0x62C, int32_t);
	CLASS_FIELD(mHealth, 0x630, int32_t);

	// xref: Mob::TickDeath
	MCAPI static void spawnOrbs(BlockSource &region, const Vec3 &pos, int32_t xpValue, DropType type, Player *owner);
};