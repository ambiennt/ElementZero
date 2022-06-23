#pragma once

#include "../dll.h"
#include "../Level/PlayerPermissionLevel.h"
#include "Core.h"

#include <string>
#include <unordered_map>

class Player;
enum class CommandPermissionLevel : int8_t;
enum class FileReadResult : int32_t {
	SUCCESS = 0,
	FAILED_TO_OPEN_FILE = 1,
	MALFORMED = 2,
};

class PermissionsFile {
	MCAPI void setDefaultPlayerPermission(class Player &player, CommandPermissionLevel opCommandPermLevel);
public:
	Core::PathBuffer<std::string> mFilePath; // 0x0
	std::unordered_map<std::string, PlayerPermissionLevel> mPermissions; // 0x20

	MCAPI void persistPlayerPermissionsToDisk(Player const& player, PlayerPermissionLevel permission);
	MCAPI void persistPlayerPermissionsToDisk(std::string const& xuid, PlayerPermissionLevel permission);
	MCAPI FileReadResult reload();
	MCAPI void applyPlayerPermissionsFromDisk(Player &player, CommandPermissionLevel opCommandPermLevel);
	MCAPI bool isPermissionsSet(std::string const &xuid, PlayerPermissionLevel playerPermLevel) const;
	MCAPI std::vector<std::string> getXUIDsByPermission(PlayerPermissionLevel playerPermLevel) const;

	inline PlayerPermissionLevel getPermissionLevelByXUID(std::string const& xuid) const {
		auto it = this->mPermissions.find(xuid);
		if (it != this->mPermissions.end()) {
			return it->second;
		}
		return PlayerPermissionLevel::Member;
	}
};

static_assert(offsetof(PermissionsFile, mPermissions) == 0x20);
static_assert(sizeof(PermissionsFile) == 0x60);