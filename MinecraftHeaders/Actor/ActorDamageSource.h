#include <hook.h>
#include "ActorUniqueID.h"
#include "ActorType.h"
#include "ActorCategory.h"
#include <cstring>

enum class ActorDamageCause {
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
	All              = 31
};

class ActorDamageSource {
public:

	virtual ~ActorDamageSource();
	virtual bool isEntitySource(void);
	virtual bool isChildEntitySource(void);
	virtual bool isBlockSource(void);
	virtual bool isFire(void);
	virtual std::string getDeathMessage(void);
	virtual bool getIsCreative(void);
	virtual bool getIsWorldBuilder(void);
	virtual struct ActorUniqueID getEntityUniqueID(void);
	virtual enum ActorType getEntityType(void)const;
	virtual enum ActorCategory getEntityCategories(void);
	virtual bool getDamagingEntityIsCreative(void);
	virtual bool getDamagingEntityIsWorldBuilder(void);
	virtual struct ActorUniqueID getDamagingEntityUniqueID(void);
	virtual enum ActorType getDamagingEntityType(void);
	virtual enum ActorCategory getDamagingEntityCategories(void);
	virtual class ActorDamageSource clone(void);

	BUILD_ACCESS_MUT(enum ActorDamageCause, mCause, 0x8);
};

class ActorDamageByActorSource : public ActorDamageSource {
public:
	BUILD_ACCESS_MUT(class BlockSource*, mRegion, 0x10);
	BUILD_ACCESS_MUT(bool, mIsWorldBuilder, 0x18);
	BUILD_ACCESS_MUT(bool, mIsCreative, 0x19);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mActorID, 0x20);
	BUILD_ACCESS_MUT(enum ActorType, mActorType, 0x28);
	BUILD_ACCESS_MUT(enum ActorCategory, mActorCategories, 0x2C);
	BUILD_ACCESS_MUT(std::string, mActorNameTag, 0x30);
};

class ActorDamageByBlockSource : public ActorDamageSource {
public:
	BUILD_ACCESS_MUT(class block*, mBlock, 0x10);
};

class ActorDamageByChildActorSource : public ActorDamageByActorSource {
public:
	BUILD_ACCESS_MUT(bool, mDamagingActorIsWorldBuilder, 0x50);
	BUILD_ACCESS_MUT(bool, mDamagingActorIsCreative, 0x51);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mDamagingActorId, 0x58);
	BUILD_ACCESS_MUT(enum ActorType, mDamagingActorType, 0x60);
	BUILD_ACCESS_MUT(enum ActorCategory, mDamagingActorCategories, 0x64);
	BUILD_ACCESS_MUT(std::string, mDamagingActorNameTag, 0x68);
};