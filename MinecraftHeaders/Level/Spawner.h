#pragma once

#include "../dll.h"
#include <modutils.h>

struct ActorDefinitionIdentifier;
class BlockSource;
class Vec3;
class Mob;
class Actor;

class Spawner {
public:

	MCAPI Mob* spawnMob(BlockSource &region, ActorDefinitionIdentifier const& id,
		Actor *spawner, Vec3 const& position, bool naturalSpawn, bool surface, bool fromSpawner);
	MCAPI Actor* spawnProjectile(BlockSource &region, ActorDefinitionIdentifier const& id,
		Actor *spawner, Vec3 const& position, Vec3 const& direction);

	BUILD_ACCESS_MUT(int32_t, mTotalEntityCount, 0xC0);
};