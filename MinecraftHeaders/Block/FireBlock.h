#pragma once

#include "BlockLegacy.h"
#include "../Math/AABB.h"
#include "../dll.h"

class FireBlock : public BlockLegacy {
public:
	AABB mAabb; // 0x1060
};

static_assert(offsetof(FireBlock, mAabb) == 0x1060);