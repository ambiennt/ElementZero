#pragma once

#include <memory>
#include <array>

#include "../Command/CommandPermissionLevel.h"
#include "PlayerPermissionLevel.h"
#include "AbilitiesIndex.h"

class PermissionsHandler {
public:
	CommandPermissionLevel mCommandPermissionsLevel;
	PlayerPermissionLevel mPlayerPermissions;
};

class Ability {
public:

	enum class Type : int8_t {
		Invalid     = 0,
		Unset       = 1,
		BooleanType = 2,
		FloatType   = 3
	};

	enum class Options : int8_t {
		None                         = 0,
		NoSave                       = 1,
		CommandExposed               = 2,
		PermissionsInterfaceExposed  = 4,
		WorldbuilderOverrides        = 8
	};

	union Value {
		bool mBoolVal;
		float mFloatVal;
	};
	
	Type mType = Type::Invalid;
	Value mValue{};
	Options mOptions = Options::None;
};

class Abilities {
public:
	std::unique_ptr<PermissionsHandler> mPermissionsHandler; // 0x0
	std::array<Ability, 18> mAbilities; // 0x8
	std::array<Ability, 8> mCustomAbilityCache; // 0xE0

	MCAPI static class std::array<char const*, 18> ABILITY_NAMES;
	MCAPI static std::string const TAG;

	MCAPI void addSaveData(class CompoundTag&) const;
	MCAPI bool loadSaveData(class CompoundTag const&);
	MCAPI void setPlayerPermissions(enum PlayerPermissionLevel);
	MCAPI void _registerAbilities();
};

static_assert(offsetof(Abilities, mPermissionsHandler) == 0x0);
static_assert(offsetof(Abilities, mAbilities) == 0x8);
static_assert(offsetof(Abilities, mCustomAbilityCache) == 0xE0);