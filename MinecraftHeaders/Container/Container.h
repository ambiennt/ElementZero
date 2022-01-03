#pragma once

#include <unordered_set>
#include <deque>
#include <vector>
#include <functional>

#include "ContainerType.h"
#include "ContainerContentChangeListener.h"
#include "ContainerSizeChangeListener.h"
#include "../Core/NBT.h"
#include "../Item/ItemStack.h"
#include "../Math/Vec3.h"

#include "../dll.h"

class Player;
class BlockSource;
class ItemDescriptor;

class Container {
public:
	ContainerType mContainerType; // 0x8
	ContainerType mGameplayContainerType; // 0x9
	std::unordered_set<ContainerContentChangeListener *> mContentChangeListeners; // 0x10
	std::unordered_set<ContainerSizeChangeListener *> mSizeChangeListeners; // 0x50
	std::deque<std::function<void(Container &, int, ItemStack const &, ItemStack const &)>> mTransactionContextStack; // 0x90
	std::string mName; // 0xB8
	bool mHasCustomName; // 0xD8
	uint32_t mContainerRuntimeId = 0; // 0xDC - SimpleRuntimeId<class ContainerRuntimeIdTag,unsigned int,0>

	MCAPI Container(enum ContainerType);
	virtual ~Container();
	virtual void init();
	virtual void serverInitItemStackIds(int, int, std::function<void(int, ItemStack const &)>);
	virtual void addContentChangeListener(ContainerContentChangeListener *);
	virtual void removeContentChangeListener(ContainerContentChangeListener *);
	virtual class ItemStack const &getItem(int) const;
	virtual bool hasRoomForItem(ItemStack const &);
	virtual void addItem(ItemStack &);
	virtual bool addItemToFirstEmptySlot(ItemStack &);
	virtual void setItem(int, ItemStack const &);
	virtual void setItemWithForceBalance(int, ItemStack const &, bool);
	virtual void removeItem(int, int);
	virtual void removeAllItems(void);
	virtual void dropContents(BlockSource &, Vec3 const &, bool);
	virtual int getContainerSize() const = 0;
	virtual int getMaxStackSize() const  = 0;
	virtual void startOpen(Player &)     = 0;
	virtual void stopOpen(Player &)      = 0;
	virtual std::vector<ItemStack> getSlotCopies() const;
	virtual std::vector<ItemStack const *> getSlots() const;
	virtual int getItemCount(ItemStack const &);
	virtual int findFirstSlotForItem(ItemStack const &);
	virtual bool canPushInItem(BlockSource &, int, int, ItemStack const &) const;
	virtual bool canPullOutItem(BlockSource &, int, int, ItemStack const &) const;
	virtual void setContainerChanged(int);
	virtual void setContainerMoved();
	virtual void setCustomName(std::string const &);
	virtual bool hasCustomName() const;
	virtual void readAdditionalSaveData(CompoundTag const &);
	virtual void addAdditionalSaveData(CompoundTag &);
	virtual void createTransactionContext(
			std::function<void(Container &, int, ItemStack const &, ItemStack const &)>, std::function<void()>);
	virtual void initializeContainerContents(BlockSource &);

	MCAPI void triggerTransactionChange(int, ItemStack const&, ItemStack const&);
};

static_assert(offsetof(Container, mContainerType) == 0x8);
static_assert(offsetof(Container, mContentChangeListeners) == 0x10);
static_assert(offsetof(Container, mSizeChangeListeners) == 0x50);
static_assert(offsetof(Container, mTransactionContextStack) == 0x90);
static_assert(offsetof(Container, mName) == 0xB8);
static_assert(offsetof(Container, mHasCustomName) == 0xD8);