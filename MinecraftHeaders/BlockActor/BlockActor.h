#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../Math/Vec3.h"
#include "../Math/AABB.h"
#include "../Block/Block.h"
#include "BlockActorType.h"
#include "BlockActorRendererId.h"

#include "../dll.h"

#include <modutils.h>

class BlockActor {
	char unknown[200];

public:
	BUILD_ACCESS_MUT(int32_t, mTickCount, 0x8);
	BUILD_ACCESS_MUT(const class Block*, mBlock, 0x10);
	BUILD_ACCESS_MUT(float, mDestroyTimer, 0x18);
	BUILD_ACCESS_MUT(class Vec3, mDestroyDirection, 0x1C);
	BUILD_ACCESS_MUT(float, mDestroyProgress, 0x28);
	BUILD_ACCESS_MUT(class BlockPos, mPosition, 0x2C);
	BUILD_ACCESS_MUT(class AABB, mAABB, 0x38);
	BUILD_ACCESS_MUT(const enum BlockActorType, mType, 0x54);
	BUILD_ACCESS_MUT(enum BlockActorRendererId, mRendererId, 0x58);
	BUILD_ACCESS_MUT(std::string, mCustomName, 0x60);
	BUILD_ACCESS_MUT(std::string, mFilteredCustomName, 0x80);
	BUILD_ACCESS_MUT(int32_t, mRepairCost, 0xA0);
	BUILD_ACCESS_MUT(bool, mClientSideOnly, 0xA4);
	BUILD_ACCESS_MUT(bool, mIsMovable, 0xA5);
	BUILD_ACCESS_MUT(bool, mSaveCustomName, 0xA6);
	BUILD_ACCESS_MUT(bool, mCanRenderCustomName, 0xA7);
	BUILD_ACCESS_MUT(const float, mSignShadowRadius, 0xA8);
	BUILD_ACCESS_MUT(class ActorTerrainInterlockData, mTerrainInterlockData, 0xB0);
	BUILD_ACCESS_MUT(bool, mChanged, 0xC8);

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

static_assert(sizeof(BlockActor) == 208);