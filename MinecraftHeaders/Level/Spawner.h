#pragma once

#include "../dll.h"
#include "../Block/BlockSource.h"
#include "../Actor/ActorDefinitionIdentifier.h"
#include "../Actor/Mob.h"
#include "../Math/Vec3.h"

class Spawner {
public:

	MCAPI Mob* spawnMob(class BlockSource &region, struct ActorDefinitionIdentifier const& id,
		Actor *spawner, Vec3 const& position, bool naturalSpawn, bool surface, bool fromSpawner);
	MCAPI Actor* spawnProjectile(class BlockSource &region, struct ActorDefinitionIdentifier const& id,
		Actor *spawner, Vec3 const& position, Vec3 const& direction);
};