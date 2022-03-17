#pragma once

#include <cstdint>

enum class ActorCategory  {
	None                     = 0x0,
	Player                   = 0x1,
	Mob                      = 0x2,
	Monster                  = 0x4,
	Humandoid                = 0x8,
	HumanoidMonster          = 0xC,
	Animal                   = 0x10,
	WaterSpawning            = 0x20,
	WaterAnimal              = 0x30,
	Pathable                 = 0x40,
	Tamable                  = 0x80,
	TamableAnimal            = 0x90,
	Ridable                  = 0x100,
	Item                     = 0x400,
	Ambient                  = 0x800,
	Villager                 = 0x1000,
	EvocationIllagerMonster  = 0x100C,
	Arthropod                = 0x2000,
	Undead                   = 0x4000,
	UndeadMob                = 0x4004,
	Zombie                   = 0x8000,
	ZombieMonster            = 0x8004,
	Minecart                 = 0x10000,
	MinecartRidable          = 0x10100,
	Boat                     = 0x20000,
	BoatRideable             = 0x20100,
	NonTargetable            = 0x40000,
};