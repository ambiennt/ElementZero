#pragma once

enum class CommandFlagValue : int8_t {
	None        = 0, // Visible
	Usage       = 1, // makes the command color blue like gametest?
	Visibility2 = 2, // HiddenFromCommandBlockOrigin
	Visibility4 = 4, // HiddenFromPlayerOrigin
	Visibility6 = 6, // Hidden
	Sync        = 8, // HiddenFromAutomationOrigin
	Removed     = 14,
	Execute     = 16,
	Type        = 32, // message/title type commands
	Cheat       = 64,
};

struct CommandFlag {
	CommandFlagValue value;

	inline bool operator==(CommandFlag const &rhs) const { return (this->value == rhs.value); }
	inline bool operator!=(CommandFlag const &rhs) const { return (this->value != rhs.value); }
	CommandFlag &operator|=(CommandFlag const &rhs) {
		this->value = (CommandFlagValue)((char)rhs.value | (char)this->value);
		return *this;
	}
};

constexpr inline CommandFlag CommandFlagNone        = {CommandFlagValue::None};
constexpr inline CommandFlag CommandFlagUsage       = {CommandFlagValue::Usage};
constexpr inline CommandFlag CommandFlagVisibility2 = {CommandFlagValue::Visibility2};
constexpr inline CommandFlag CommandFlagVisibility4 = {CommandFlagValue::Visibility4};
constexpr inline CommandFlag CommandFlagVisibility6 = {CommandFlagValue::Visibility6};
constexpr inline CommandFlag CommandFlagSync        = {CommandFlagValue::Sync};
constexpr inline CommandFlag CommandFlagRemoved     = {CommandFlagValue::Removed};
constexpr inline CommandFlag CommandFlagExecute     = {CommandFlagValue::Execute};
constexpr inline CommandFlag CommandFlagType        = {CommandFlagValue::Type};
constexpr inline CommandFlag CommandFlagCheat       = {CommandFlagValue::Cheat};

/*
- requires operator but NOT cheats (ex: /gamerule): flag 1: 64, flag 2: 0, permission level: 1
- requires operator AND cheats (ex: /give):         flag 1: 0, flag 2: 0, permission level: 1
- server console only (ex: /whitelist):             flag 1: 0, flag 2: 0, permission level: 4
- does NOT require operator or cheats (ex: /me):    flag 1: 64, flag 2: 0, permission level: 0
- requires operator AND cheats, and shows as light blue color (ex: /gametest): flag 1: 1, flag 2: 0, permission level: 1
- requires operator but NOT cheats, and shows as light blue color: flag 1: 64, flag 2: 1, permission level: 1

- it doesn't matter if you flip the 1st and 2nd command flag, the command will still behave the same
*/