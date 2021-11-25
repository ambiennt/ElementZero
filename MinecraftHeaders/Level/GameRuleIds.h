#pragma once

enum class GameRuleIds {
	CommandBlockOutput      = 0,
	DoDaylightCycle         = 1,
	DoEntityDrops           = 2,
	DoFireTick              = 3,
	DoMobLoot               = 4,
	DoMobSpawning           = 5,
	DoTileDrops             = 6,
	DoWeatherCycle          = 7,
	DrowningDamage          = 8,
	FallDamage              = 9,
	FireDamage              = 10,
	KeepInventory           = 11,
	MobGriefing             = 12,
	Pvp                     = 13,
	ShowCoordinates         = 14,
	NaturalRegeneration     = 15,
	TntExplodes             = 16,
	SendCommandFeedback     = 17,
	Experimental            = 18,
	MaxCommandChainLength   = 19,
	DoInsomnia              = 20,
	CommandBlocksEnabled    = 21,
	RandomTickSpeed         = 22,
	DoImmediateRespawn      = 23,
	ShowDeathMessages       = 24,
	FunctionCommandLimit    = 25,
	SpawnRadius             = 26,
	ShowTags                = 27,
	VanillaGameRuleCount    = 28,
	GlobalMute              = 29,
	AllowDestructiveObjects = 30,
	CodeBuilder             = 31,
	EducationGameRuleCount  = 32
};