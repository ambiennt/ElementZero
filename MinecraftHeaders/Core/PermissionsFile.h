#pragma once

#include "../dll.h"
#include "../Level/PlayerPermissionLevel.h"
#include "Core.h"

#include <string>
#include <unordered_map>

class Player;

class PermissionsFile {
public:
	Core::PathBuffer<std::string> mFilePath; // 0x0
	std::unordered_map<std::string, PlayerPermissionLevel> mPermissions; // 0x20

	MCAPI void persistPlayerPermissionsToDisk(Player const& player, PlayerPermissionLevel permission);
	MCAPI void persistPlayerPermissionsToDisk(std::string const& xuid, PlayerPermissionLevel permission);
};

static_assert(offsetof(PermissionsFile, mPermissions) == 0x20);
static_assert(sizeof(PermissionsFile) == 0x60);