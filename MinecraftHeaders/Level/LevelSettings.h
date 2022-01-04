#pragma once

#include "GameType.h"
#include "Difficulty.h"
#include "Level.h"
#include "LevelDataWrapper.h"
#include "GeneratorType.h"
#include "Abilities.h"
#include "GameRules.h"
#include "../dll.h"

#include <optional>
#include <vector>
#include <string>

#include <modutils.h>

class LevelSettings {
public:
	BUILD_ACCESS_MUT(uint32_t, mSeed, 0x0);
	BUILD_ACCESS_MUT(enum GameType, mGameType, 0x4);
	BUILD_ACCESS_MUT(enum Difficulty, mGameDifficulty, 0x8); // 4 byte array
	BUILD_ACCESS_MUT(bool, mForceGameType, 0xC);
	BUILD_ACCESS_MUT(enum GeneratorType, mGenerator, 0x10);
	BUILD_ACCESS_MUT(enum NetherWorldType, mNetherType, 0x14);
	BUILD_ACCESS_MUT(class SpawnSettings, mSpawnSettings, 0x18);
	BUILD_ACCESS_MUT(bool, mAchievementsDisabled, 0x48);
	BUILD_ACCESS_MUT(int32_t, mTime, 0x4C);
	BUILD_ACCESS_MUT(class EducationEditionOfferValue, mEducationEditionOffer, 0x50);
	BUILD_ACCESS_MUT(bool, mEducationFeaturesEnabled, 0x54);
	BUILD_ACCESS_MUT(bool, mImmutableWorld, 0x55);
	BUILD_ACCESS_MUT(float, mRainLevel, 0x58);
	BUILD_ACCESS_MUT(float, mLightningLevel, 0x5C);
	BUILD_ACCESS_MUT(bool, mConfirmedPlatformLockedContent, 0x60);
	BUILD_ACCESS_MUT(bool, mMultiplayerGameIntent, 0x61);
	BUILD_ACCESS_MUT(bool, mLANBroadcastIntent, 0x62);
	BUILD_ACCESS_MUT(int32_t, mXBLBroadcastIntent, 0x64); // enum Social::GamePublishSetting
	BUILD_ACCESS_MUT(int32_t, mPlatformBroadcastIntent, 0x68); // enum Social::GamePublishSetting
	BUILD_ACCESS_MUT(bool, mCommandsEnabled, 0x6C);
	BUILD_ACCESS_MUT(bool, mTexturePacksRequired, 0x6D);
	BUILD_ACCESS_MUT(bool, mHasLockedBehaviorPack, 0x6E);
	BUILD_ACCESS_MUT(bool, mHasLockedResourcePack, 0x6F);
	BUILD_ACCESS_MUT(bool, mIsFromLockedTemplate, 0x70);
	BUILD_ACCESS_MUT(bool, mUseMsaGamertagsOnly, 0x71);
	BUILD_ACCESS_MUT(bool, mOverrideSettings, 0x72);
	BUILD_ACCESS_MUT(bool, mBonusChestEnabled, 0x73);
	BUILD_ACCESS_MUT(bool, mStartWithMapEnabled, 0x74);
	BUILD_ACCESS_MUT(int32_t, mServerChunkTickRange, 0x78);
	BUILD_ACCESS_MUT(bool, mForceExperimentalGameplay, 0xC);
	BUILD_ACCESS_MUT(bool, mIsFromWorldTemplate, 0x7D);
	BUILD_ACCESS_MUT(bool, mIsWorldTemplateOptionLocked, 0x7E);
	BUILD_ACCESS_MUT(bool, mSpawnV1Villagers, 0x7F);
	BUILD_ACCESS_MUT(int32_t, mLimitedWorldWidth, 0x80);
	BUILD_ACCESS_MUT(int32_t, mLimitedWorldDepth, 0x84);
	BUILD_ACCESS_MUT(class Abilities, mDefaultAbilities, 0x88);
	BUILD_ACCESS_MUT(class BlockPos, mDefaultSpawn, 0x1C8);
	BUILD_ACCESS_MUT(std::vector<class PackInstanceId>, mNewWorldBehaviorPackIdentities, 0x1D8);
	BUILD_ACCESS_MUT(std::vector<class PackInstanceId>, mNewWorldResourcePackIdentities, 0x1F0);
	BUILD_ACCESS_MUT(class GameRules, mGameRules, 0x208);
	BUILD_ACCESS_MUT(class BaseGameVersion, mBaseGameVersion, 0x220);
	BUILD_ACCESS_MUT(std::string, mEducationProductID, 0x290);
	BUILD_ACCESS_MUT(std::string, mBiomeOverride, 0x2B0);
	BUILD_ACCESS_MUT(std::optional<class EducationLevelSettings>, mEducationLevelSettings, 0x2D0);
	BUILD_ACCESS_MUT(std::optional<bool>, mOverrideForceExperimentalGameplayFlag, 0x390);
};