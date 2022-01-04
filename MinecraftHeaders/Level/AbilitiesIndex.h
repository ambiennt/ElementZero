#pragma once

enum class AbilitiesIndex : int16_t { // this is actually an int16 in bds
	Invalid              = -1,
	Build                = 0,
	Mine                 = 1,
	DoorsAndSwitches     = 2,
	OpenContainers       = 3,
	AttackPlayers        = 4,
	AttackMobs           = 5,
	OperatorCommands     = 6,
	Teleport             = 7,
	ExposedAbilityCount  = 8,
	Invulnerable         = 8, // both are 8
	Flying               = 9,
	MayFly               = 10,
	Instabuild           = 11,
	Lightning            = 12,
	FlySpeed             = 13,
	WalkSpeed            = 14,
	Muted                = 15,
	WorldBuilder         = 16,
	NoClip               = 17,
	AbilityCount         = 18
};