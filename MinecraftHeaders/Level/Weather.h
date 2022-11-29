#pragma once

#include "Level.h"
#include "Dimension.h"
#include "../dll.h"

#include <modutils.h>

class Weather : public LevelListener {
public:

	CLASS_FIELD(mNoise, 0x8, class PerlinSimplexNoise);
	CLASS_FIELD(mTick, 0x30, int32_t); // idk why this is an int32
	CLASS_FIELD(mORainLevel, 0x34, float);
	CLASS_FIELD(mRainLevel, 0x38, float);
	CLASS_FIELD(mTargetRainLevel, 0x3C, float);
	CLASS_FIELD(mOLightningLevel, 0x40, float);
	CLASS_FIELD(mLightningLevel, 0x44, float);
	CLASS_FIELD(mTargetLightningLevel, 0x48, float);
	CLASS_FIELD(mFogLevel, 0x4C, float);
	CLASS_FIELD(mSkyFlashTime, 0x50, int32_t);
	CLASS_FIELD(mDimension, 0x58, class Dimension *);

	MCAPI void _notifyWeatherChangedEvent(class LevelData const&) const;
	MCAPI int32_t calcRainCycleTime() const;
	MCAPI int32_t calcRainDuration() const;
	MCAPI int32_t calcSnowBlockDepth(class BlockSource &region, class BlockPos const& pos, int32_t maxLayerDepth) const;
	MCAPI bool canPlaceTopSnow(class BlockSource &region, class BlockPos const& pos, bool fromFallingSnow, bool checkSnowDepthLevel, int32_t* newHeightAfterPlacement) const; // yes this is a pointer to int
	MCAPI bool isPrecipitatingAt(class BlockSource &region, class BlockPos const& pos) const;
	MCAPI bool isRainingAt(class BlockSource &region, class BlockPos const& pos) const;
	MCAPI bool isSnowingAt(class BlockSource &region, class BlockPos const& pos) const;
	MCAPI void rebuildTopSnowToDepth(class BlockSource &region, class BlockPos const& pos, int32_t desiredDepth);
	MCAPI void serverTick();
	MCAPI bool tryToPlaceTopSnow(class BlockSource &region, class BlockPos const& pos, bool fromFallingSnow, bool fillLowerNeighborsFirst);
};