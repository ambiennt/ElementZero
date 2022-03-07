#pragma once

#include <cstdint>

// this enum is actually an int32_t but doing left shift bitwise
// operations can cause UB with first bit being the sign
enum class ActorCategory : uint32_t {
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