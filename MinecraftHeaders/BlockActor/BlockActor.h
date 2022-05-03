#pragma once

#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "../Math/AABB.h"
#include "ActorTerrainInterlockData.h"
#include "../dll.h"

#include <string>
#include <vector>

class Block;

enum class BlockActorType : int32_t;
enum class BlockActorRendererId : int32_t;

class BlockActor {
public:
	int32_t mTickCount; // 0x8
	const Block* mBlock; // 0x10
	float mDestroyTimer; // 0x18
	Vec3 mDestroyDirection; // 0x1C
	float mDestroyProgress; // 0x28
	BlockPos mPosition; // 0x2C
	AABB mAABB; // 0x38
	const BlockActorType mType; // 0x54
	BlockActorRendererId mRendererId; // 0x58
	std::string mCustomName; // 0x60
	std::string mFilteredCustomName; // 0x80
	int32_t mRepairCost; // 0xA0
	bool mClientSideOnly; // 0xA4
	bool mIsMovable; // 0xA5
	bool mSaveCustomName; // 0xA6
	bool mCanRenderCustomName; // 0xA7
	const float mSignShadowRadius; // 0xA8
	ActorTerrainInterlockData mTerrainInterlockData; // 0xB0
	bool mChanged; // 0xC8

	MCAPI BlockActor(enum BlockActorType, class BlockPos const &, std::string const &);

	virtual ~BlockActor();
	virtual void load(class Level &, class CompoundTag const &, class DataLoadHelper &);
	virtual bool save(class CompoundTag &) const;
	virtual bool saveItemInstanceData(class CompoundTag &);
	virtual void saveBlockData(class CompoundTag &, class BlockSource &) const;
	virtual void loadBlockData(class CompoundTag const &, class BlockSource &, class DataLoadHelper &);
	virtual void onCustomTagLoadDone(class BlockSource &);
	virtual void tick(class BlockSource &);
	virtual bool isFinished();
	virtual void onChanged(class BlockSource &);
	virtual bool isMovable(class BlockSource &);
	virtual bool isCustomNameSaved();
	virtual void onPlace(class BlockSource &);
	virtual void onMove();
	virtual void onRemoved(class BlockSource &);
	virtual void triggerEvent(int, int);
	virtual void clearCache();
	virtual void onNeighborChanged(class BlockSource &, class BlockPos const &);
	virtual float getShadowRadius(class BlockSource &) const;
	virtual bool hasAlphaLayer() const;
	virtual class BlockActor *getCrackEntity(class BlockSource &, class BlockPos const &);
	virtual void getDebugText(std::vector<std::string> &, class BlockPos const &);
	virtual std::string const &getCustomName() const;
	virtual std::string const &getFilteredCustomName(class UIProfanityContext const &);
	virtual std::string getName() const;
	virtual void setCustomName(std::string const &) const;
	virtual std::string getImmersiveReaderText(class BlockSource &);
	virtual int getRepairCost() const;
	virtual class PistonBlockActor *getOwningPiston(class BlockSource &);
	virtual class Container *getContainer();
	virtual class Container const *getContainer() const;
	virtual float getDeletionDelayTimeSeconds() const;
	virtual void onChunkLoaded(class LevelChunk &);
	virtual void onChunkUnloaded(class LevelChunk &);

protected:
	virtual void _onUpdatePacket(class CompoundTag const &, class BlockSource &);
	virtual bool _playerCanUpdate(class Player const &) const;
};

static_assert(sizeof(BlockActor) == 0xD0);