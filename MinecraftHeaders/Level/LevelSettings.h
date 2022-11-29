#pragma once

#include "GameType.h"
#include "Difficulty.h"
#include "Level.h"
#include "LevelData.h"
#include "LevelDataWrapper.h"
#include "GeneratorType.h"
#include "Abilities.h"
#include "GameRules.h"
#include "SpawnSettings.h"
#include "../Core/Social.h"
#include "../Core/SemVersion.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

#include <optional>
#include <vector>
#include <string>

class alignas(8) EducationLevelSettings {
public:
	uint8_t pad[0xB8];
};
static_assert(sizeof(EducationLevelSettings) == 0xB8);

class LevelSettings {
public:
	uint32_t mSeed; // 0x0
	GameType mGameType; // 0x4
	Difficulty mGameDifficulty; // 0x8
	bool mForceGameType; // 0xC
	GeneratorType mGenerator; // 0x10
	NetherWorldType mNetherType; // 0x14
	SpawnSettings mSpawnSettings; // 0x18
	bool mAchievementsDisabled; // 0x48
	int32_t mTime; // 0x4C
	EducationEditionOfferValue mEducationEditionOffer; // 0x50
	bool mEducationFeaturesEnabled; // 0x54
	bool mImmutableWorld; // 0x55
	float mRainLevel; // 0x58
	float mLightningLevel; // 0x5C
	bool mConfirmedPlatformLockedContent; // 0x60
	bool mMultiplayerGameIntent; // 0x61
	bool mLANBroadcastIntent; // 0x62
	Social::GamePublishSetting mXBLBroadcastIntent; // 0x64
	Social::GamePublishSetting mPlatformBroadcastIntent; // 0x68
	bool mCommandsEnabled; // 0x6C
	bool mTexturePacksRequired; // 0x6D
	bool mHasLockedBehaviorPack; // 0x6E
	bool mHasLockedResourcePack; // 0x6F
	bool mIsFromLockedTemplate; // 0x70
	bool mUseMsaGamertagsOnly; // 0x71
	bool mOverrideSettings; // 0x72
	bool mBonusChestEnabled; // 0x73
	bool mStartWithMapEnabled; // 0x74
	int32_t mServerChunkTickRange; // 0x78
	bool mForceExperimentalGameplay; // 0x7C
	bool mIsFromWorldTemplate; // 0x7D
	bool mIsWorldTemplateOptionLocked; // 0x7E
	bool mSpawnV1Villagers; // 0x7F
	int32_t mLimitedWorldWidth; // 0x80
	int32_t mLimitedWorldDepth; // 0x84
	Abilities mDefaultAbilities; // 0x88
	BlockPos mDefaultSpawn; // 0x1C8
	std::vector<PackInstanceId> mNewWorldBehaviorPackIdentities; // 0x1D8
	std::vector<PackInstanceId> mNewWorldResourcePackIdentities; // 0x1F0
	GameRules mGameRules; // 0x208
	BaseGameVersion mBaseGameVersion; // 0x220
	std::string mEducationProductID; // 0x290
	std::string mBiomeOverride; // 0x2B0
	std::optional<EducationLevelSettings> mEducationLevelSettings; // 0x2D0
	std::optional<bool> mOverrideForceExperimentalGameplayFlag; // 0x390
};
static_assert(sizeof(LevelSettings) == 0x398);