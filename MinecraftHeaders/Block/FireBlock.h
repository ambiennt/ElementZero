#pragma once

#include "BlockLegacy.h"
#include "../Math/AABB.h"
#include "../dll.h"

#include "modutils.h"

class FireBlock : public BlockLegacy {
public:
	BUILD_ACCESS_MUT(class AABB, mAabb, 0x1060);
};