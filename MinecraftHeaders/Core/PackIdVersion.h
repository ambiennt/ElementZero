#pragma once

#include "mce.h"
#include "SemVersion.h"

enum struct PackType {
	Invalid          = 0,
	Addon            = 1,
	Cached           = 2,
	CopyProtected    = 3,
	Behavior         = 4,
	PersonaPiece     = 5,
	Resources        = 6,
	Skins            = 7,
	WorldTemplate    = 8,
	PackTypeCount    = 9
};

struct PackIdVersion {
	mce::UUID mUUID; // 0x0
	SemVersion mVersion; // 0x10
	PackType mPackType; // 0x80
};

static_assert(offsetof(PackIdVersion, mUUID) == 0x0);
static_assert(offsetof(PackIdVersion, mVersion) == 0x10);
static_assert(offsetof(PackIdVersion, mPackType) == 0x80);
static_assert(sizeof(PackIdVersion) == 0x88);