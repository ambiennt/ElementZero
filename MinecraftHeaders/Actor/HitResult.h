#pragma once

#include <cstdint>

#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"

#include "../dll.h"

class Actor;

enum class HitResultType : int32_t {
	TILE                = 0x0,
	ENTITY              = 0x1,
	ENTITY_OUT_OF_RANGE = 0x2,
	NO_HIT              = 0x3
};

class HitResult {
public:
	Vec3 mStartPos; // 0x0
	Vec3 mRayDir; // 0xC
	HitResultType mType; // 0x18
	uint8_t mFacing; // 0x1C
	BlockPos mBlock; // 0x20
	Vec3 mPos; // 0x2C
	Actor* mEntity; // 0x38
	bool mIsHitLiquid; // 0x40
	uint8_t mLiquidFacing; // 0x41
	BlockPos mLiquid; // 0x44
	Vec3 mLiquidPos; // 0x50
	bool mIndirectHit; // 0x5C
};

static_assert(offsetof(HitResult, mType) == 0x18);
static_assert(offsetof(HitResult, mPos) == 0x2C);
static_assert(offsetof(HitResult, mIsHitLiquid) == 0x40);
static_assert(offsetof(HitResult, mIndirectHit) == 0x5C);
static_assert(sizeof(HitResult) == 0x60);