#pragma once

#include "../dll.h"
#include "../Container/RandomizableBlockActorFillingContainer.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorUniqueID.h"
#include "../Level/Level.h"

#include <functional>
#include <set>
#include <modutils.h>

class ChestBlockActor : public RandomizableBlockActorFillingContainer {
public:

	enum class Flags {
		mPairLead = 1,
		mPairingChanged = 2,
		mAlongX = 3,
		mDeferredPairLoad = 4,
		mConverted = 5
	};

	/*float mSpeed; // 0x1F8
	bool mIsGlobalChest; // 0x1FC
	bool mUsesLegacyBlockDetection; // 0x1FD
	float mObstructionHeight; // 0x200
	float mOpenness; // 0x204
	float mOldOpenness; // 0x208
	bool mIsOpen; // 0x20C
	int32_t mTickInterval; // 0x210
	uint32_t mFlags; // 0x214 - bit flags - use ChestBlockActor::hasBitFlag(enum ChestBlockActor::Flags)
	int32_t mDeferredPairX; // 0x218
	int32_t mDeferredPairZ; // 0x21C
	ChestBlockActor* mLargeChestPaired; // 0x220
	BlockPos mLargeChestPairedPosition; // 0x228
	bool mIsTrappedChest; // 0x234
	bool mIsFindable; // 0x235
	std::unordered_set<ActorUniqueID> mOpenedByIds; // 0x238
	bool mNotifyPlayersOnChange; // 0x278*/

	BUILD_ACCESS_MUT(float, mSpeed, 0x1F8);
	BUILD_ACCESS_MUT(bool, mIsGlobalChest, 0x1FC);
	BUILD_ACCESS_MUT(bool, mUsesLegacyBlockDetection, 0x1FD);
	BUILD_ACCESS_MUT(float, mObstructionHeight, 0x200);
	BUILD_ACCESS_MUT(float, mOpenness, 0x204);
	BUILD_ACCESS_MUT(float, mOldOpenness, 0x208);
	BUILD_ACCESS_MUT(bool, mIsOpen, 0x20C);
	BUILD_ACCESS_MUT(int32_t, mTickInterval, 0x210);
	BUILD_ACCESS_MUT(uint32_t, mFlags, 0x214); // bit flags - use ChestBlockActor::hasBitFlag(enum ChestBlockActor::Flags)
	BUILD_ACCESS_MUT(int32_t, mDeferredPairX, 0x218);
	BUILD_ACCESS_MUT(int32_t, mDeferredPairZ, 0x21C);
	BUILD_ACCESS_MUT(class ChestBlockActor *, mLargeChestPaired, 0x220);
	BUILD_ACCESS_MUT(class BlockPos, mLargeChestPairedPosition, 0x228);
	BUILD_ACCESS_MUT(bool, mIsTrappedChest, 0x234);
	BUILD_ACCESS_MUT(bool, mIsFindable, 0x235);
	BUILD_ACCESS_MUT(std::unordered_set<struct ActorUniqueID>, mOpenedByIds, 0x238);
	BUILD_ACCESS_MUT(bool, mNotifyPlayersOnChange, 0x278);

	MCAPI ChestBlockActor(enum BlockActorType type, std::string const& id, enum BlockActorRendererId renderId, class BlockPos const& pos, bool isTrapped);
	virtual ~ChestBlockActor();
	/*virtual void load(class Level &, class CompoundTag const&, class DataLoadHelper &);
	virtual bool save(class CompoundTag &);
	virtual bool saveItemInstanceData(class CompoundTag &);
	virtual void saveBlockData(class CompoundTag &, class BlockSource &);
	virtual void loadBlockData(class CompoundTag const&, class BlockSource &, class DataLoadHelper &);
	virtual void onCustomTagLoadDone(class BlockSource &);
	virtual void tick(class BlockSource &);
	virtual bool isFinished(void);
	virtual void onChanged(class BlockSource &);
	virtual bool isMovable(class BlockSource &);
	virtual bool isCustomNameSaved(void);
	virtual void onPlace(class BlockSource &);
	virtual void onMove(void);
	virtual void onRemoved(class BlockSource &);
	virtual void triggerEvent(int32_t, int32_t);
	virtual void clearCache(void);
	virtual void onNeighborChanged(class BlockSource &, class BlockPos const&);
	virtual float getShadowRadius(class BlockSource &);
	virtual bool hasAlphaLayer(void);
	virtual class ChestBlockActor* getCrackEntity(class BlockSource &, class BlockPos const&);
	virtual void getDebugText(std::vector<std::string> &, BlockPos const&);
	virtual std::string getCustomName(void);
	virtual std::string getFilteredCustomName(class UIProfanityContext const&);
	virtual std::string getName(void);
	virtual void setCustomName(std::string const&);
	virtual std::string getImmersiveReaderText(class BlockSource &);
	virtual int32_t getRepairCost(void);
	virtual class PistonBlockActor* getOwningPiston(class BlockSource &);
	virtual class Container* getContainer(void);
	virtual class Container const* getContainer(void) const;
	virtual int32_t getDeletionDelayTimeSeconds(void);
	virtual void onChunkLoaded(class LevelChunk &);
	virtual void onChunkUnloaded(class LevelChunk &);
	virtual std::unique_ptr<class BlockActorDataPacket> _getUpdatePacket(class BlockSource &);
	virtual void _onUpdatePacket(class CompoundTag const&, class BlockSource &);
	virtual bool _playerCanUpdate(class Player const&);
	virtual void setContainerChanged(int32_t);
	virtual void startOpen(class Player &);
	virtual void dropContents(class BlockSource &, class Vec3 const&, bool);
	virtual void initializeContainerContents(class BlockSource &);
	virtual int32_t getContainerSize(void);
	virtual int32_t getMaxStackSize(void);
	virtual class ItemStack const& getItem(int32_t);
	virtual void setItem(int32_t, class ItemStack const&);
	virtual void serverInitItemStackIds(int32_t, int32_t, std::function<void ()(int32_t, ItemStack const&)>);
	virtual void loadItems(class CompoundTag const&, Level&);
	virtual void saveItems(class CompoundTag &);
	virtual void stopOpen(class Player &);
	virtual int32_t clearInventory(int32_t);
	virtual bool canPushInItem(class BlockSource &, int32_t, int32_t, class ItemInstance const&);
	virtual bool canPullOutItem(class BlockSource &, int32_t, int32_t, class ItemInstance const&);
	virtual void addContentChangeListener(class ContainerContentChangeListener *);
	virtual void removeContentChangeListener(class ContainerContentChangeListener *);
	virtual void playOpenSound(class BlockSource &);
	virtual void playCloseSound(class BlockSource &);
	virtual bool _canOpenThis(class BlockSource &);
	virtual class AABB* getObstructionAABB(void);
	virtual bool _detectEntityObstruction(class BlockSource &);*/

	MCAPI void _closeChest(class BlockSource &region, class Player *player);
	MCAPI bool _detectBlockObstruction(class BlockSource &region);
	MCAPI bool _saveClientSideState(class CompoundTag &tag);
	MCAPI void _unpair(void);
	MCAPI bool canPairWith(class BlockActor *actor, class BlockSource &region);
	MCAPI void forceCloseChest(class BlockSource &region);
	MCAPI void pairWith(class ChestBlockActor *chest, bool isLeadingChest);
	MCAPI void unpair(class BlockSource &region);

	inline bool hasBitFlag(enum ChestBlockActor::Flags flag) {
		return this->mFlags & (uint32_t)flag;
	}
};

/*static_assert(offsetof(ChestBlockActor, mSpeed) == 0x1F8);
static_assert(offsetof(ChestBlockActor, mIsOpen) == 0x20C);
static_assert(offsetof(ChestBlockActor, mTickInterval) == 0x210);
static_assert(offsetof(ChestBlockActor, mLargeChestPaired) == 0x220);
static_assert(offsetof(ChestBlockActor, mOpenedByIds) == 0x238);
static_assert(offsetof(ChestBlockActor, mNotifyPlayersOnChange) == 0x278);*/