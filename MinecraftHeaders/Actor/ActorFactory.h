#pragma once

#include "../dll.h"
#include "Actor.h"

#include <memory>
#include <modutils.h>

class ActorFactory {
public:
	BUILD_ACCESS_MUT(class Level *, mLevel, 0x0);
	BUILD_ACCESS_MUT(std::shared_ptr<class IEntityInitializer>, mEntityInitializer, 0x8);
	BUILD_ACCESS_MUT(class ActorComponentFactory, mComponentFactory, 0x18);
	BUILD_ACCESS_MUT(class ActorGoalFactory, mActorFactory, 0x60);

	MCAPI std::unique_ptr<Actor> createSpawnedEntity(ActorDefinitionIdentifier const &id, Actor *spawner, Vec3 const &pos, Vec2 const &rot);
};