#pragma once

#include <functional>
#include <set>

#include "../Core/AutomaticID.h"
#include "../Net/NetworkIdentifier.h"
#include "../Actor/ActorUniqueID.h"
#include "LevelChunk.h"
#include "LevelListener.h"
#include "SavedData.h"
#include "DimensionID.h"
#include "BeardAndShaverStorage.h"

#include "../dll.h"

class BaseLightTextureImageBuilder;
class DimensionBrightnessRamp;
class BlockEventDispatcher;
class TaskGroup;
class PostprocessingManager;
class ChunkSource;
class WorldGenerator;
class Weather;
class Seasons;
class CircuitSystem;
class TickingAreaList;
class RuntimeLightingManager;
class LevelChunkBuilderData;
class ChunkBuildOrderPolicyBase;
class VillageManager;
class Color;
class Packet;
class Player;

class Dimension : public LevelListener, public SavedData {
public:

	Level* mLevel; // 0x38
	int16_t mSeaLevel; // 0x40
	std::unique_ptr<BlockSource> mBlockSource; // 0x48
	float mMobsPerChunkSurface[7]; // 0x50
	float mMobsPerChunkUnderground[7]; // 0x6C
	BrightnessPair mDefaultBrightness; // 0x88
	std::unique_ptr<BaseLightTextureImageBuilder> mLightTextureImageBuilder; // 0x90
	std::unique_ptr<DimensionBrightnessRamp> mDimensionBrightnessRamp; // 0x98
	std::string mName; // 0xA0
	DimensionID mDimensionId; // AutomaticID<class Dimension, int32_t> - 0xC0
	bool mUltraWarm; // 0xC4
	bool mHasCeiling; // 0xC5
	bool mHasWeather; // 0xC6
	bool mHasSkylight; // 0xC7
	Brightness mSkyDarken; // 0xC8
	int16_t mHeight; // 0xCA
	std::unique_ptr<BlockEventDispatcher> mDispatcher; // 0xD0
	std::unique_ptr<TaskGroup> mTaskGroup; // 0xD8
	std::unique_ptr<PostprocessingManager> mPostProcessingManager; // 0xE0
	std::unique_ptr<ChunkSource> mChunkSource; // 0xE8
	WorldGenerator* mWorldGenerator; // 0xF0
	std::unique_ptr<Weather> mWeather; // 0xF8
	std::unique_ptr<Seasons> mSeasons; // 0x100
	std::unique_ptr<CircuitSystem> mCircuitSystem; // 0x108
	int32_t CIRCUIT_TICK_RATE; // const int32_t - 0x110
	int32_t mCircuitSystemTickRate; // 0x114
	std::unordered_map<ActorUniqueID, Actor **> mEntityIdLookup; // std::unordered_map<struct ActorUniqueID, gsl::not_null<class Actor *>> - 0x118
	BeardAndShaverStorage mBeardandShaverStorage; // 0x158
	std::unordered_map<ChunkPos, std::vector<std::unique_ptr<CompoundTag>>> mLimboEntities; // 0x1A0
	std::vector<Actor *> mEntitiesToMoveChunks; // 0x1E0
	std::unique_ptr<TickingAreaList> mTickingAreaList; // 0x1F8
	LevelChunkGarbageCollector mLevelChunkGarbageCollector; // 0x200
	std::set<ActorUniqueID> mWitherIDs; // 0x478
	std::unique_ptr<RuntimeLightingManager> mRuntimeLightingManager; // 0x488
	std::unique_ptr<LevelChunkBuilderData> mLevelChunkBuilderData; // 0x490
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int64_t, std::ratio<1, 1000000000>>> mLastPruneTime; // 0x498
	std::unique_ptr<ChunkBuildOrderPolicyBase> mChunkBuildOrderPolicy; // 0x4A0
	std::unique_ptr<VillageManager> mVillageManager; // 0x4A8
	std::vector<NetworkIdentifierWithSubId> mTemporaryPlayerIds; // 0x4B0

	virtual void init();
	virtual void tick();
	virtual void tickRedstone();
	virtual std::tuple<std::unique_ptr<ChunkSource>, WorldGenerator *> createGenerator();
	virtual bool isNaturalDimension();
	virtual bool isValidSpawn(int32_t, int32_t) const;
	virtual Color getBrightnessDependentFogColor(Color const &, float) const;
	virtual float getMaxFogEnd() const;
	virtual float getMaxFogStart() const;
	virtual bool isFoggyAt(int32_t, int32_t) const;
	virtual float getCloudHeight() const;
	virtual int getDefaultBiome() const;
	virtual bool mayRespawnViaBed() const;
	virtual bool hasGround() const;
	virtual class BlockPos getSpawnPos() const;
	virtual int getSpawnYPosition() const;
	virtual bool hasBedrockFog();
	virtual float getClearColorScale();
	virtual bool showSky();
	virtual bool isDay() const;
	virtual float getTimeOfDay(int32_t, float) const;
	virtual float getSunIntensity(float, Vec3 const &, float) const;
	virtual void forceCheckAllNeighChunkSavedStat() const;
	virtual class Vec3 translatePosAcrossDimension(Vec3 const &, AutomaticID<Dimension, int>) const;
	virtual void sendBroadcast(Packet const &, Player *);
	virtual bool isPositionRelevantForPlayer(BlockPos const &, Player &) const;
	virtual bool isEntityRelevantForPlayer(Player &, Actor const &) const;
	virtual class BaseLightTextureImageBuilder *getLightTextureImageBuilder() const;
	virtual class DimensionBrightnessRamp const &getBrightnessRamp() const;
	virtual void startLeaveGame();
	virtual std::unique_ptr<ChunkBuildOrderPolicyBase> _createChunkBuildOrderPolicy();

	MCAPI void sendPacketForEntity(Actor const&, Packet const&, Player const*);
	MCAPI void forEachPlayer(std::function<bool(Player &)>);
	MCAPI void forEachPlayer(std::function<bool(Player const &)>) const;
};

static_assert(offsetof(Dimension, mLevel) == 0x38);
static_assert(offsetof(Dimension, mMobsPerChunkSurface) == 0x50);
static_assert(sizeof(Dimension) == 0x4C8);