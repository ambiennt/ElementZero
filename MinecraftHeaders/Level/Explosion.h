#pragma once

#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "../Actor/ActorUniqueID.h"
#include "../Core/Random.h"

#include <unordered_set>
#include <optional>

class BlockSource;

class Explosion {
public:
	Vec3 mPos; // 0x0
	float mRadius; // 0xC
	std::unordered_set<BlockPos> mToBlow; // 0x10
	bool mFire; // 0x50
	bool mBreaking;
	bool mAllowUnderwater; // 0x52
	ActorUniqueID mSourceID; // 0x58
	BlockSource* mRegion; // 0x60
	float mMaxResistance; // 0x68
	std::optional<bool> mInWaterOverride; // 0x6C
	Random mRandom; // 0x70
};

static_assert(sizeof(Explosion) == 0xA98);