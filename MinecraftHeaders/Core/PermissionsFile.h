#pragma once

#include "../dll.h"
#include "../Level/PlayerPermissionLevel.h"
#include "Core.h"

#include <string>
#include <unordered_map>

class PermissionsFile {
public:
	Core::PathBuffer<std::string> mFilePath; // 0x0
	std::unordered_map<std::string, PlayerPermissionLevel> mPermissions; // 0x20
};

static_assert(offsetof(PermissionsFile, mPermissions) == 0x20);
static_assert(sizeof(PermissionsFile) == 0x60);