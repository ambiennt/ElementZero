#pragma once

#include "../dll.h"
#include "Actor.h"

#include <memory>
#include <modutils.h>

class ActorFactory {
public:
	CLASS_FIELD(mLevel, 0x0, class Level *);
	CLASS_FIELD(mEntityInitializer, 0x8, std::shared_ptr<class IEntityInitializer>);
	CLASS_FIELD(mComponentFactory, 0x18, class ActorComponentFactory);
	CLASS_FIELD(mActorFactory, 0x60, class ActorGoalFactory);

	MCAPI std::unique_ptr<Actor> createSpawnedEntity(ActorDefinitionIdentifier const &id, Actor *spawner, Vec3 const &pos, Vec2 const &rot);
};