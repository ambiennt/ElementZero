#pragma once

#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "Actor.h"

#include <modutils.h>
#include "../dll.h"

enum class HitResultType {
	TILE                = 0x0,
	ENTITY              = 0x1,
	ENTITY_OUT_OF_RANGE = 0x2,
	NO_HIT              = 0x3
};

class HitResult {
public:

	BUILD_ACCESS_MUT(class Vec3, mStartPos, 0x0);
	BUILD_ACCESS_MUT(class Vec3, mRayDir, 0xC);
	BUILD_ACCESS_MUT(enum HitResultType, mType, 0x18);
	BUILD_ACCESS_MUT(uint8_t, mFacing, 0x1C);
	BUILD_ACCESS_MUT(class BlockPos, mBlock, 0x20);
	BUILD_ACCESS_MUT(class Vec3, mPos, 0x2C);
	BUILD_ACCESS_MUT(class Actor*, mEntity, 0x38);
	BUILD_ACCESS_MUT(bool, mIsHitLiquid, 0x40);
	BUILD_ACCESS_MUT(uint8_t, mLiquidFacing, 0x41);
	BUILD_ACCESS_MUT(class BlockPos, mLiquid, 0x44);
	BUILD_ACCESS_MUT(class Vec3, mLiquidPos, 0x50);
	BUILD_ACCESS_MUT(bool, mIndirectHit, 0x5C);
};