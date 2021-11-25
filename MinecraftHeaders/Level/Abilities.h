#pragma once

#include <memory>
#include <array>

#include "../Command/CommandPermissionLevel.h"
#include "PlayerPermissionLevel.h"

enum class AbilitiesIndex {
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
	Invulnerable         = 8,
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

class PermissionsHandler {
public:
	CommandPermissionLevel mCommandPermissionsLevel;
	PlayerPermissionLevel mPlayerPermissions;
};

class Ability {
public:
	enum class Type : char {
		Invalid  = 0,
		Unset    = 1,
		Boolean  = 2,
		Float    = 3
	};

	enum class Options : char {
		None                         = 0,
		NoSave                       = 1,
		CommandExposed               = 2,
		PermissionsInterfaceExposed  = 4,
		WorldbuilderOverrides        = 8
	};

	union Value {
		bool val_bool;
		float val_float;
		Value(bool flag) { val_bool = flag; }
		Value(float val) { val_float = val; }
		Value() {}
	};
	Type type = Type::Invalid;
	Value value{};
	Options opts = Options::None;
};

class Abilities {
public:
	std::unique_ptr<PermissionsHandler> mPermissionsHandler;
	std::array<Ability, 18> Abilities;
	std::array<Ability, 8> CustomAbilities;

	MCAPI static class std::array<char const*, 18> ABILITY_NAMES;
	MCAPI static std::string const TAG;

	MCAPI void addSaveData(class CompoundTag&) const;
	MCAPI bool loadSaveData(class CompoundTag const&);
	MCAPI void setPlayerPermissions(enum PlayerPermissionLevel);
	MCAPI void _registerAbilities();
};