#include <hook.h>
#include "ActorUniqueID.h"
#include "ActorType.h"
#include <cstring>

class ActorUniqueID;
enum class ActorType;

enum class ActorCategory {
    None                     = 0,
    Player                   = 1,
    Mob                      = 2,
    Monster                  = 4,
    Humandoid                = 8,
    HumanoidMonster          = 12,
    Animal                   = 16,
    WaterSpawning            = 32,
    WaterAnimal              = 48,
    Pathable                 = 64,
    Tamable                  = 128,
    TamableAnimal            = 144,
    Ridable                  = 256,
    Item                     = 1024,
    Ambient                  = 2048,
    Villager                 = 4096,
    EvocationIllagerMonster  = 4108,
    Arthropod                = 8192,
    Undead                   = 16384,
    UndeadMob                = 16388,
    Zombie                   = 32768,
    ZombieMonster            = 32772,
    Minecart                 = 65536,
    MinecartRidable          = 65792,
    Boat                     = 131072,
    BoatRideable             = 131328,
    NonTargetable            = 262144
};

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