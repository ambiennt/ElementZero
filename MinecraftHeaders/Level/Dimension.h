#pragma once

#include <memory>
#include <string>
#include <functional>
#include <set>
#include <chrono>

#include <modutils.h>

#include "../Core/AutomaticID.h"
#include "LevelListener.h"
#include "SavedData.h"
#include "DimensionID.h"
#include "../dll.h"

class Dimension : public LevelListener, public SavedData {
public:

	BUILD_ACCESS_MUT(class Level*, mLevel, 0x38);
	BUILD_ACCESS_MUT(int16_t, mSeaLevel, 0x40);
	BUILD_ACCESS_MUT(std::unique_ptr<class BlockSource>, mBlockSource, 0x48);

	using floatArr7 = float[7];
	BUILD_ACCESS_MUT(floatArr7, mMobsPerChunkSurface, 0x50);
	BUILD_ACCESS_MUT(floatArr7, mMobsPerChunkUnderground, 0x6C);

	BUILD_ACCESS_MUT(struct BrightnessPair, mDefaultBrightness, 0x88);
	BUILD_ACCESS_MUT(std::unique_ptr<class BaseLightTextureImageBuilder>, mLightTextureImageBuilder, 0x90);
	BUILD_ACCESS_MUT(std::unique_ptr<class DimensionBrightnessRamp>, mDimensionBrightnessRamp, 0x98);
	BUILD_ACCESS_MUT(std::string, mName, 0xA0);

	//using dimensionId = AutomaticID<class Dimension, int32_t>;
	//BUILD_ACCESS_MUT(dimensionId, mDimensionId, 0xC0);
	BUILD_ACCESS_MUT(enum DimensionID, mDimensionId, 0xC0);

	BUILD_ACCESS_MUT(bool, mUltraWarm, 0xC4);
	BUILD_ACCESS_MUT(bool, mHasCeiling, 0xC5);
	BUILD_ACCESS_MUT(bool, mHasWeather, 0xC6);
	BUILD_ACCESS_MUT(bool, mHasSkylight, 0xC7);
	BUILD_ACCESS_MUT(struct Brightness, mSkyDarken, 0xC8);
	BUILD_ACCESS_MUT(int16_t, mHeight, 0xCA);
	BUILD_ACCESS_MUT(std::unique_ptr<class BlockEventDispatcher>, mDispatcher, 0xD0);
	BUILD_ACCESS_MUT(std::unique_ptr<class TaskGroup>, mTaskGroup, 0xD8);
	BUILD_ACCESS_MUT(std::unique_ptr<class PostprocessingManager>, mPostProcessingManager, 0xE0);
	BUILD_ACCESS_MUT(std::unique_ptr<class ChunkSource>, mChunkSource, 0xE8);
	BUILD_ACCESS_MUT(class WorldGenerator*, mWorldGenerator, 0xF0);
	BUILD_ACCESS_MUT(std::unique_ptr<class Weather>, mWeather, 0xF8);
	BUILD_ACCESS_MUT(std::unique_ptr<class Seasons>, mSeasons, 0x100);
	BUILD_ACCESS_MUT(std::unique_ptr<class CircuitSystem>, mCircuitSystem, 0x108);
	BUILD_ACCESS_MUT(const int32_t, CIRCUIT_TICK_RATE, 0x110);
	BUILD_ACCESS_MUT(int32_t, mCircuitSystemTickRate, 0x114);
	//BUILD_ACCESS_MUT(std::unordered_map<struct ActorUniqueID, gsl::not_null<class Actor *>>, mEntityIdLookup, 0x118);
	BUILD_ACCESS_MUT(class BeardAndShaverStorage, mBeardandShaverStorage, 0x158); // wtf

	using limboEntityMap = std::unordered_map<class ChunkPos, std::vector<std::unique_ptr<class CompoundTag>>>;
	BUILD_ACCESS_MUT(limboEntityMap, mLimboEntities, 0x1A0);

	BUILD_ACCESS_MUT(std::vector<class Actor *>, mEntitiesToMoveChunks, 0x1E0);
	BUILD_ACCESS_MUT(std::unique_ptr<class TickingAreaList>, mTickingAreaList, 0x1F8);
	BUILD_ACCESS_MUT(class LevelChunkGarbageCollector, mLevelChunkGarbageCollector, 0x200);
	BUILD_ACCESS_MUT(std::set<struct ActorUniqueID>, mWitherIDs, 0x478);
	BUILD_ACCESS_MUT(std::unique_ptr<class RuntimeLightingManager>, mRuntimeLightingManager, 0x488);
	BUILD_ACCESS_MUT(std::unique_ptr<class LevelChunkBuilderData>, mLevelChunkBuilderData, 0x490);
	
	using pruneTime1000000000 = std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int64_t, std::ratio<1, 1000000000>>>;
	BUILD_ACCESS_MUT(pruneTime1000000000, mLastPruneTime, 0x498);

	BUILD_ACCESS_MUT(std::unique_ptr<class ChunkBuildOrderPolicyBase>, mChunkBuildOrderPolicy, 0x4A0);
	BUILD_ACCESS_MUT(std::unique_ptr<class VillageManager>, mVillageManager, 0x4A8);
	BUILD_ACCESS_MUT(std::vector<class NetworkIdentifierWithSubId>, mTemporaryPlayerIds, 0x4B0);

	virtual ~Dimension();
	virtual void init(void);
	virtual void tick(void);
	virtual void tickRedstone(void);
	virtual class std::tuple<std::unique_ptr<class ChunkSource>, class WorldGenerator *> createGenerator(void);
	virtual bool isNaturalDimension();
	virtual bool isValidSpawn(int, int) const;
	virtual class Color getBrightnessDependentFogColor(class Color const &, float) const;
	virtual float getMaxFogEnd(void) const;
	virtual float getMaxFogStart(void) const;
	virtual bool isFoggyAt(int, int) const;
	virtual float getCloudHeight(void) const;
	virtual int getDefaultBiome() const;
	virtual bool mayRespawnViaBed() const;
	virtual bool hasGround() const;
	virtual class BlockPos getSpawnPos() const;
	virtual int getSpawnYPosition() const;
	virtual bool hasBedrockFog();
	virtual float getClearColorScale(void);
	virtual bool showSky();
	virtual bool isDay(void) const;
	virtual float getSunIntensity(float, class Vec3 const &, float) const;
	virtual void forceCheckAllNeighChunkSavedStat() const;
	virtual class Vec3 translatePosAcrossDimension(class Vec3 const &, class AutomaticID<class Dimension, int>) const;
	virtual void deserialize(class CompoundTag const &);
	virtual void serialize(class CompoundTag &) const;
	virtual void sendBroadcast(class Packet const &, class Player *);
	virtual bool isPositionRelevantForPlayer(class BlockPos const &, class Player &) const;
	virtual bool isEntityRelevantForPlayer(class Player &, class Actor const &) const;
	virtual class BaseLightTextureImageBuilder *getLightTextureImageBuilder(void) const;
	virtual class DimensionBrightnessRamp const &getBrightnessRamp(void) const;
	virtual void startLeaveGame(void);
	virtual float getTimeOfDay(int, float) const;
	virtual std::unique_ptr<class ChunkBuildOrderPolicyBase> _createChunkBuildOrderPolicy(void);

	MCAPI void sendPacketForEntity(class Actor const&, class Packet const&, class Player const*);
	MCAPI void forEachPlayer(std::function<bool(Player &)>);
	MCAPI void forEachPlayer(std::function<bool(Player const &)>) const;
};