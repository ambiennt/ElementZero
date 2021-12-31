#pragma once

#include "Level.h"
#include "Dimension.h"
#include "../dll.h"

#include <modutils.h>

class Weather : public LevelListener {
public:

	BUILD_ACCESS_MUT(class PerlinSimplexNoise, mNoise, 0x8);
	BUILD_ACCESS_MUT(int32_t, mTick, 0x30); // idk why this is an int32
	BUILD_ACCESS_MUT(float, mORainLevel, 0x34);
	BUILD_ACCESS_MUT(float, mRainLevel, 0x38);
	BUILD_ACCESS_MUT(float, mTargetRainLevel, 0x3C);
	BUILD_ACCESS_MUT(float, mOLightningLevel, 0x40);
	BUILD_ACCESS_MUT(float, mLightningLevel, 0x44);
	BUILD_ACCESS_MUT(float, mTargetLightningLevel, 0x48);
	BUILD_ACCESS_MUT(float, mFogLevel, 0x4C);
	BUILD_ACCESS_MUT(int32_t, mSkyFlashTime, 0x50);
	BUILD_ACCESS_MUT(class Dimension *, mDimension, 0x58);

	MCAPI void _notifyWeatherChangedEvent(class LevelData const&);
	MCAPI int32_t calcRainCycleTime(void);
	MCAPI int32_t calcRainDuration(void);
	MCAPI int32_t calcSnowBlockDepth(class BlockSource &region, class BlockPos const& pos, int32_t maxLayerDepth);
	MCAPI bool canPlaceTopSnow(class BlockSource &region, class BlockPos const& pos, bool fromFallingSnow, bool checkSnowDepthLevel, int32_t* newHeightAfterPlacement); // yes this is a pointer to int
	MCAPI bool isPrecipitatingAt(class BlockSource &region, class BlockPos const& pos);
	MCAPI bool isRainingAt(class BlockSource &region, class BlockPos const& pos);
	MCAPI bool isSnowingAt(class BlockSource &region, class BlockPos const& pos);
	MCAPI void levelEvent(enum LevelEvent type, Vec3 const& pos, int32_t data); // this func only handles LevelEvent enum types: 0xBBB, 0xBB9, 0xBBA, 0xBBC
	MCAPI void rebuildTopSnowToDepth(class BlockSource &region, class BlockPos const& pos, int32_t desiredDepth);
	MCAPI void serverTick(void);
	MCAPI bool tryToPlaceTopSnow(class BlockSource &region, class BlockPos const& pos, bool fromFallingSnow, bool fillLowerNeighborsFirst);
};