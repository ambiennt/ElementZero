#pragma once

#include <string>
#include <variant>
#include <unordered_map>

#include "../Core/json.h"
#include "../Core/SemVersion.h"
#include "../Core/NBT.h"
#include "../Core/StringKey.h"
#include "../Core/Social.h"
#include "../Math/BlockPos.h"
#include "AdventureSettings.h"
#include "WorldTemplateLevelData.h"
#include "GameRules.h"
#include "Abilities.h"
#include "GameVersion.h"
#include "Tick.h"
#include "GameType.h"
#include "Difficulty.h"
#include "GeneratorType.h"
#include "SpawnSettings.h"

#include "../dll.h"

enum class NetherWorldType : int8_t {
	Normal = 0,
	Flat   = 1
};

enum class EducationEditionOffer : int32_t {
	None        = 0,
	RestOfWorld = 1,
	China       = 2,
};

class EducationEditionOfferValue {
public:
	EducationEditionOffer mValue;
};

struct LevelDataValue : public std::variant<int, bool, float, std::string, GeneratorType,
GameType, BlockPos, uint32_t, std::unique_ptr<CompoundTag>> {
	using variant::variant;
};

namespace LevelDataKeys {

extern MCAPI StringKey EDUCATION_OID;
extern MCAPI StringKey GAME_TYPE;
extern MCAPI StringKey GENERATOR;
extern MCAPI StringKey LIMITED_WORLD_DEPTH;
extern MCAPI StringKey LIMITED_WORLD_WIDTH;
extern MCAPI StringKey LOADED_PLAYER_TAG;
extern MCAPI StringKey SEED;
extern MCAPI StringKey SPAWN_POS;

}; // namespace LevelDataKeys

// ref: LevelData::getTagData
class LevelData {
public:
	AdventureSettings mAdventureSettings;
	WorldTemplateLevelData mWorldTemplateLevelData;
	GameRules mGameRules;
	Abilities mAbilities;
	std::string mLevelName;
	int32_t mStorageVersion;
	GameVersion mMinCompatibleClientVersion;
	int32_t mNetworkVersion;
	SemVersion mInventoryVersion;
	Tick mCurrentTick;
	bool mHasSpawnPos;
	BlockPos mLimitedWorldOrigin;
	int32_t mDayCycleTime;
	uint64_t mLastPlayedTime;
	uint32_t mServerChunkTickRange;
	float mRainLevel;
	uint32_t mRainTime;
	float mLightningLevel;
	uint32_t mLightningTime;
	uint32_t mNetherScale;
	GameVersion mLastOpenedWithVersion;
	GameType mGameType;
	bool mForceGameType;
	bool mSpawnMobs;
	Json::Value mFlatworldGeneratorOptions;
	int32_t mWorldStartCount;
	bool mAchievementsDisabled;
	EducationEditionOffer mEducationEditionOffer;
	bool mEducationFeaturesEnabled;
	bool mSingleUseWorld;
	bool mConfirmedPlatformLockedContent;
	bool mMultiplayerGameIntent;
	bool mIsMultiplayerGame;
	bool mLANBroadcastIntent;
	bool mLANBroadcast;
	Social::GamePublishSetting mXBLBroadcastIntent;
	Social::GamePublishSetting mXBLBroadcastMode;
	Social::GamePublishSetting mPlatformBroadcastIntent;
	Social::GamePublishSetting mPlatformBroadcastMode;
	bool mCommandsEnabled;
	bool mTexturepacksRequired;
	bool mLockedBehaviorPack;
	bool mLockedResourcePack;
	bool mIsFromLockedTemplate;
	std::string mEducationProductId;
	bool mUseMsaGamertagsOnly;
	bool mBonusChestEnabled;
	bool mBonusChestSpawned;
	bool mStartWithMapEnabled;
	bool mMapsCenteredToOrigin;
	bool mRequiresCopiedPackRemovalCheck;
	bool mOnlySpawnV1Villagers;
	NetherWorldType mNetherType;
	SpawnSettings mSpawnSettings;
	std::unordered_map<StringKey, LevelDataValue> mKV, mAltKV;
	std::string mBiomeOverride;

private:
	template <typename T> T const *_extractValue(StringKey const &) const;

public:
	inline LevelDataValue const *getValue(StringKey const &key) const {
		if (auto kv = mKV.find(key); kv != mKV.end()) return &kv->second;
		if (auto kv = mAltKV.find(key); kv != mAltKV.end()) return &kv->second;
		return nullptr;
	}
	template <typename T> inline T const *extractValue(StringKey const &key) const {
		auto val = getValue(key);
		return std::get_if<T>(val);
	}
	template <typename T> inline void setValue(StringKey const &key, T value) { mKV[key] = LevelDataValue(value); }

	inline BlockPos getSpawnPos() const {
		auto value = this->extractValue<BlockPos>(LevelDataKeys::SPAWN_POS);
		if (value) { return *value; }
		return BlockPos::ZERO;
	}
	inline void setSpawnPos(BlockPos const &pos) { this->setValue(LevelDataKeys::SPAWN_POS, pos); }

	inline GameType getGameType() const {
		auto value = this->extractValue<::GameType>(LevelDataKeys::GAME_TYPE);
		if (value) { return *value; }
		return GameType::Survival;
	}
	inline void setGameType(GameType type) { this->setValue(LevelDataKeys::GAME_TYPE, type); }

	inline uint32_t getSeed() const {
		auto value = this->extractValue<uint32_t>(LevelDataKeys::SEED);
		if (value) { return *value; }
		return 0;
	}
	inline void setSeed(uint32_t seed) { this->setValue(LevelDataKeys::SEED, seed); }

	inline GeneratorType getWorldGenerator() const {
		auto value = this->extractValue<GeneratorType>(LevelDataKeys::GENERATOR);
		if (value) { return *value; }
		return GeneratorType::Overworld;
	}
	inline void setWorldGenerator(GeneratorType seed) { this->setValue(LevelDataKeys::SEED, seed); }

	inline int32_t getLimitedWorldWidth() const {
		auto value = this->extractValue<int32_t>(LevelDataKeys::LIMITED_WORLD_WIDTH);
		if (value) { return *value; }
		return 0;
	}
	inline void setLimitedWorldWidth(int32_t value) { this->setValue(LevelDataKeys::LIMITED_WORLD_WIDTH, value); }

	inline int32_t getLimitedWorldDepth() const {
		auto value = this->extractValue<int32_t>(LevelDataKeys::LIMITED_WORLD_DEPTH);
		if (value) { return *value; }
		return 0;
	}
	inline void setLimitedWorldDepth(int32_t value) { this->setValue(LevelDataKeys::LIMITED_WORLD_DEPTH, value); }

	inline DimensionID getSpawnDimension() const { return this->mSpawnSettings.mDim; }
	inline void setSpawnDimension(DimensionID d) { this->mSpawnSettings.mDim = d; }

};

static_assert(offsetof(LevelData, mGameRules) == 288);
static_assert(offsetof(LevelData, mAbilities) == 312);
static_assert(offsetof(LevelData, mLevelName) == 632);
static_assert(offsetof(LevelData, mMinCompatibleClientVersion) == 672);
static_assert(offsetof(LevelData, mNetworkVersion) == 728);
static_assert(offsetof(LevelData, mInventoryVersion) == 736);
static_assert(offsetof(LevelData, mCurrentTick) == 848);
static_assert(offsetof(LevelData, mLimitedWorldOrigin) == 860);
static_assert(offsetof(LevelData, mDayCycleTime) == 872);
static_assert(offsetof(LevelData, mServerChunkTickRange) == 888);
static_assert(offsetof(LevelData, mSingleUseWorld) == 1005);
static_assert(offsetof(LevelData, mCommandsEnabled) == 0x404);
static_assert(offsetof(LevelData, mEducationProductId) == 1040);
static_assert(offsetof(LevelData, mNetherType) == 1079);
static_assert(offsetof(LevelData, mSpawnSettings) == 1080);
static_assert(offsetof(LevelData, mKV) == 1128);