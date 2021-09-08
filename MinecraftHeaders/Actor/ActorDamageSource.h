#include <hook.h>
#include "ActorUniqueID.h"
#include "ActorType.h"
#include <cstring>

class ActorUniqueID;
enum class ActorType;
enum class ActorCategory;

enum class ActorDamageCause {
	None             = -1,
	Override         = 0,
	Contact          = 1,
	EntityAttack     = 2,
	Projectile_0     = 3,
	Suffocation      = 4,
	Fall_0           = 5,
	Fire_1           = 6,
	FireTick         = 7,
	Lava_2           = 8,
	Drowning         = 9,
	BlockExplosion   = 10,
	EntityExplosion  = 11,
	Void             = 12,
	Suicide          = 13,
	Magic            = 14,
	Wither           = 15,
	Starve           = 16,
	Anvil_1          = 17,
	Thorns_0         = 18,
	FallingBlock_0   = 19,
	Piston_0         = 20,
	FlyIntoWall      = 21,
	Magma            = 22,
	Fireworks_0      = 23,
	Lightning_0      = 24,
	Charging         = 25,
	Temperature      = 26,
	All_0            = 31
};

class ActorDamageSource {
public:

	MCAPI virtual ~ActorDamageSource();
	MCAPI virtual bool isEntitySource(void);
	MCAPI virtual bool isChildEntitySource(void);
	MCAPI virtual bool isBlockSource(void);
	MCAPI virtual bool isFire(void);
	MCAPI virtual std::string getDeathMessage(void);
	MCAPI virtual bool getIsCreative(void);
	MCAPI virtual bool getIsWorldBuilder(void);
	MCAPI virtual class ActorUniqueID getEntityUniqueID(void);
	MCAPI virtual enum ActorType getEntityType(void)const;
	MCAPI virtual enum ActorCategory getEntityCategories(void);
	MCAPI virtual bool getDamagingEntityIsCreative(void);
	MCAPI virtual bool getDamagingEntityIsWorldBuilder(void);
	MCAPI virtual class ActorUniqueID getDamagingEntityUniqueID(void);
	MCAPI virtual enum ActorType getDamagingEntityType(void);
	MCAPI virtual enum ActorCategory getDamagingEntityCategories(void);
	MCAPI virtual class ActorDamageSource clone(void);
};