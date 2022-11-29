#pragma once

#include <modutils.h>
#include "../Block/BlockLegacy.h"
#include "../Actor/ActorDefinitionIdentifier.h"
#include "../Math/BlockPos.h"
#include "../Level/Difficulty.h"
#include "../dll.h"

#include <cstdint>
#include <string>
#include <functional>
#include <unordered_set>

class Random;
class Mob;

struct MobSpawnHerdInfo {
	int32_t mMinCount;
	int32_t mMaxCount;
	int32_t mHerdEventSkipCount;
	int32_t mInitialEventCount;
	std::string mInitialEvent;
	std::string mHerdEvent;
};
static_assert(sizeof(MobSpawnHerdInfo) == 0x50);

struct MobSpawnerPermutation {
	uint8_t pad[0x8]; // WeighedRandom::WeighedRandomItem
	ActorDefinitionIdentifier mId;
};
static_assert(sizeof(MobSpawnerPermutation) == 0xB0);

struct SpawnConditions {
	bool mIsOnSurface;
	bool mIsInWater;
	bool mIsInLava;
	bool mIsUnderground;
	uint64_t mDelayEndWorldAge;
	int32_t mRawBrightness;
	BlockPos mPos;
};
static_assert(sizeof(SpawnConditions) == 0x20);

class MobSpawnRules {
public:
	int32_t mMinBrightness;
	int32_t mMaxBrightness;
	float mMinMoonBrightness;
	float mMaxMoonBrightness;
	bool mAdjustForWeather;
	int32_t mMinHeight;
	int32_t mMaxHeight;
	int32_t mRarity;
	int32_t mSurfaceCap;
	int32_t mUndergroundCap;
	Difficulty mMinDifficulty;
	Difficulty mMaxDifficulty;
	int32_t mMinSpawnDistance;
	int32_t mMaxSpawnDistance;
	int32_t mSpawnDistanceCap;
	bool mSurfaceSpawner;
	bool mUndergroundSpawner;
	bool mWaterSpawner;
	bool mLavaSpawner;
	int32_t mPlayerInVillageDistance;
	int32_t mPlayerInVillageBorderTolerance;
	bool mExperimentalSpawner;
	uint64_t mMinWorldAge;
	uint64_t mMaxWorldAge;
	int32_t mMinDelay;
	int32_t mMaxDelay;
	std::vector<MobSpawnHerdInfo> mHerdList;
	std::vector<MobSpawnerPermutation> mPermutationList;
	std::string mMobEventName;
	std::unordered_set<BlockLegacy const *> mSpawnOnBlockList;
	std::unordered_set<BlockLegacy const *> mSpawnOnBlockPreventedList;
	std::vector<MobSpawnerPermutation> mGuaranteedList;
	std::string mMobToDelayId;
	int32_t mDelaySpawnChance;
	bool mPersistence;

	MCAPI static int32_t const MIN_DEFAULT_SPAWN_DISTANCE = 24;
	MCAPI static int32_t const MAX_WORLD_AGE              = 0xFFFFFFFF;
	MCAPI static int32_t const MAX_DEFAULT_SPAWN_DISTANCE = 44;

	MCAPI class MobSpawnRules * addPermutation(int32_t, int32_t, class ActorDefinitionIdentifer const&);
	MCAPI struct MobSpawnHerdInfo * selectRandomHerd(class Random &);
	MCAPI bool canSpawnInConditions(struct SpawnConditions const&, class BlockSource&);
	MCAPI int32_t getSpawnCount(struct SpawnConditions const&, class BlockSource&, class Random&, struct MobSpawnHerdInfo const&);
	
	// xref: MobSpawnRules::getPopulationCap
	inline int32_t getPopulationCap(const SpawnConditions &conditions) const {
		return conditions.mIsOnSurface ? this->mSurfaceCap : this->mUndergroundCap;
	}
};
static_assert(offsetof(MobSpawnRules, mSurfaceCap) == 0x20);
static_assert(offsetof(MobSpawnRules, mUndergroundCap) == 0x24);
static_assert(sizeof(MobSpawnRules) == 0x178);

struct MobSpawnerData {
	uint8_t pad[0x8]; // WeighedRandom::WeighedRandomItem
	ActorDefinitionIdentifier mIdentifier;
	MobSpawnRules mSpawnRules;
	std::function<void (std::vector<Mob *> &, Random &)> mOnSpawnHerd;
	std::function<ActorDefinitionIdentifier (Random &)> mOnSelectEntity;
};
static_assert(offsetof(MobSpawnerData, mIdentifier) == 0x8);
static_assert(offsetof(MobSpawnerData, mSpawnRules) == 0xB0);
static_assert(sizeof(MobSpawnerData) == 0x2A8);