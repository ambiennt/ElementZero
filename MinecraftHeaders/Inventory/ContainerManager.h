#pragma once

#include "ItemStackNetManager.h"
#include "../Container/ContainerType.h"
#include "../Core/ContainerID.h"
#include "../Item/ItemStack.h"
#include "../dll.h"

class ContainerModel; // TODO

class IContainerManager {
public:
	virtual ~IContainerManager();
	virtual ContainerID getContainerId(void);
	virtual void setContainerId(enum ContainerID id);
	virtual ContainerType getContainerType(void);
	virtual void setContainerType(enum ContainerType type);
	virtual void serverInitItemStackIds(void);
	virtual std::vector<ItemStack> getItemCopies(void);
	virtual void setSlot(int slot, const ItemStack& stack, bool fromNetwork);
	virtual ItemStack& getSlot(int slot);
	virtual void setData(int id, int value);
	virtual void broadcastChanges(void);
};

class ContainerManagerModel : public IContainerManager {
public:
	Player *mPlayer; // 0x8
	std::vector<ItemStack> mLastSlots; // 0x10
	ContainerID mContainerId; // 0x28
	ContainerType mContainerType; // 0x29
	std::function<void(ContainerManagerModel &)> mInformControllerOfDestructionCallback; //0x30
	std::unordered_map<std::string, std::shared_ptr<ContainerModel>> mContainers; // 0x70
};

static_assert(offsetof(ContainerManagerModel, mPlayer) == 0x8);
static_assert(offsetof(ContainerManagerModel, mLastSlots) == 0x10);
static_assert(offsetof(ContainerManagerModel, mContainerId) == 0x28);
static_assert(offsetof(ContainerManagerModel, mContainerType) == 0x29);
static_assert(offsetof(ContainerManagerModel, mInformControllerOfDestructionCallback) == 0x30);
static_assert(offsetof(ContainerManagerModel, mContainers) == 0x70);