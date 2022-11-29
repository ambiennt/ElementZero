#pragma once

#include "../Core/StringKey.h"
#include "../dll.h"
#include <modutils.h>

#include <array>
#include <unordered_map>

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

	CLASS_FIELD(mEntityTypeCount, 0x40, std::array<std::unordered_map<StringKey, int32_t>, 2>);
	CLASS_FIELD(mTotalEntityCount, 0xC0, int32_t);
};