#pragma once

#include <memory>
#include <string>
#include <functional>

#include <modutils.h>

#include "../Core/AutomaticID.h"
#include "LevelListener.h"
#include "SavedData.h"
#include "../dll.h"

class Dimension : public LevelListener, public SavedData {
public:
	using Id = AutomaticID<Dimension, int>;
	class Level *mLevel;
	short mSeaLevel;
	std::unique_ptr<class BlockSource> mBlockSource;

	// TODO: add all dimension fields
	BUILD_ACCESS(Id, DimensionId, 192);

	MCAPI void sendPacketForEntity(class Actor const&, class Packet const&, class Player const*);
	MCAPI void forEachPlayer(std::function<bool(Player &)>);
	MCAPI void forEachPlayer(std::function<bool(Player const &)>) const;
	
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
};

static_assert(offsetof(Dimension, mSeaLevel) == 64);