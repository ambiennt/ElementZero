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
	ContainerType type;
	std::unordered_set<ContainerContentChangeListener *> content_change_listeners;
	std::unordered_set<ContainerSizeChangeListener *> content_size_listeners;
	std::deque<std::function<void(Container &, int, ItemStack const &, ItemStack const &)>> transactions;
	std::string custom_name;
	bool has_custom_name;
	//SimpleRuntimeId<class ContainerRuntimeIdTag,unsigned int,0> container_runtime_id;

	MCAPI Container(ContainerType);
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

static_assert(offsetof(Container, type) == 0x8);
static_assert(offsetof(Container, content_change_listeners) == 0x10);
static_assert(offsetof(Container, content_size_listeners) == 0x50);
static_assert(offsetof(Container, custom_name) == 0xB8);