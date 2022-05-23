#pragma once

#include "ActorUniqueID.h"
#include "../dll.h"

class BlockSource;
class Block;
class Actor;

enum class ActorType : int32_t;
enum class ActorCategory : int32_t;

enum class ActorDamageCause : int32_t {
	None             = -1,
	Override         = 0,
	Contact          = 1,
	EntityAttack     = 2,
	Projectile       = 3,
	Suffocation      = 4,
	Fall             = 5,
	Fire             = 6,
	FireTick         = 7,
	Lava             = 8,
	Drowning         = 9,
	BlockExplosion   = 10,
	EntityExplosion  = 11,
	Void             = 12,
	Suicide          = 13,
	Magic            = 14,
	Wither           = 15,
	Starve           = 16,
	Anvil            = 17,
	Thorns           = 18,
	FallingBlock     = 19,
	Piston           = 20,
	FlyIntoWall      = 21,
	Magma            = 22,
	Fireworks        = 23,
	Lightning        = 24,
	Charging         = 25,
	Temperature      = 26,
	All              = 31,
};

class ActorDamageSource {
public:

	virtual ~ActorDamageSource();
	virtual bool isEntitySource() const;
	virtual bool isChildEntitySource() const;
	virtual bool isBlockSource() const;
	virtual bool isFire() const;
	virtual std::pair<std::string, std::vector<std::string>> getDeathMessage(std::string deadName, Actor *dead) const;
	virtual bool getIsCreative() const;
	virtual bool getIsWorldBuilder() const;
	virtual ActorUniqueID getEntityUniqueID() const;
	virtual ActorType getEntityType() const;
	virtual ActorCategory getEntityCategories() const;
	virtual bool getDamagingEntityIsCreative() const;
	virtual bool getDamagingEntityIsWorldBuilder() const;
	virtual ActorUniqueID getDamagingEntityUniqueID() const;
	virtual ActorType getDamagingEntityType() const;
	virtual ActorCategory getDamagingEntityCategories() const;
	virtual std::unique_ptr<ActorDamageSource> clone() const;

	ActorDamageCause mCause; // 0x8

	ActorDamageSource() : mCause(ActorDamageCause::None) {}
	ActorDamageSource(ActorDamageCause cause) : mCause(cause) {}
};

class ActorDamageByActorSource : public ActorDamageSource {
public:
	BlockSource* mRegion; // 0x10
	bool mIsWorldBuilder; // 0x18
	bool mIsCreative; // 0x19
	ActorUniqueID mActorID; // 0x20
	ActorType mActorType; // 0x28
	ActorCategory mActorCategories; // 0x2C
	std::string mActorNameTag; // 0x30

	MCAPI ActorDamageByActorSource(Actor &, ActorDamageCause);
};

class ActorDamageByBlockSource : public ActorDamageSource {
public:
	const Block* mBlock; // 0x10
};

class RemovedActorDamageByType : public ActorDamageSource {
public:
	ActorType mActorType; // 0x10
};

class ActorDamageByChildActorSource : public ActorDamageByActorSource {
public:
	bool mDamagingActorIsWorldBuilder; // 0x50
	bool mDamagingActorIsCreative; // 0x51
	ActorUniqueID mDamagingActorId; // 0x58
	ActorType mDamagingActorType; // 0x60
	ActorCategory mDamagingActorCategories; // 0x64
	std::string mDamagingActorNameTag; //  0x68

	MCAPI ActorDamageByChildActorSource(Actor &childActor, Actor &parent, ActorDamageCause cause); // example: projectile is child, shooter is parent
};

static_assert(offsetof(ActorDamageSource, mCause) == 0x8);
static_assert(offsetof(ActorDamageByActorSource, mActorCategories) == 0x2C);
static_assert(offsetof(ActorDamageByBlockSource, mBlock) == 0x10);
static_assert(offsetof(ActorDamageByChildActorSource, mDamagingActorNameTag) == 0x68);