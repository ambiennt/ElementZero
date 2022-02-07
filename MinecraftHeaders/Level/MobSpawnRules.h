#pragma once

#include <modutils.h>
#include "../Block/BlockLegacy.h"
#include "../Actor/ActorDefinitionIdentifier.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

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

struct MobSpawnerPermutation {
	char pad[0x8]; // WeighedRandom::WeighedRandomItem
	ActorDefinitionIdentifier mId;
};

struct SpawnConditions {
	bool mIsOnSurface;
	bool mIsInWater;
	bool mIsInLava;
	bool mIsUnderground;
	uint64_t mDelayEndWorldAge;
	int32_t mRawBrightness;
	BlockPos mPos;
};

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
	int32_t mMinDifficulty;
	int32_t mMaxDifficulty;
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
	std::vector<MobSpawnHerdInfo> mHerdList;
	ActorDefinitionIdentifier mPermutationList;
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
	MCAPI bool canSpawnInConditions(struct SpawnConditions const&, BlockSource&);
	MCAPI int32_t getSpawnCount(struct SpawnConditions const&, class BlockSource&, class Random&, struct MobSpawnHerdInfo const&);
};

struct MobSpawnerData {
	char pad[0x8]; // WeighedRandom::WeighedRandomItem
	ActorDefinitionIdentifier mIdentifier;
	MobSpawnRules mSpawnRules;
	std::function<void(std::vector<Mob *> &, Random &)> mOnSpawnHerd;
	std::function<ActorDefinitionIdentifier (Random &)> mOnSelectEntity;
};