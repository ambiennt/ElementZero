#pragma once

#include "../Container/ContainerType.h"
#include "../Core/ContainerID.h"
#include "../Item/ItemStack.h"
#include "../dll.h"

class ContainerModel; // TODO

class IContainerManager {
public:
	virtual ~IContainerManager();
	virtual ContainerID getContainerId() = 0;
	virtual void setContainerId(ContainerID id) = 0;
	virtual ContainerType getContainerType() = 0;
	virtual void setContainerType(ContainerType type) = 0;
	virtual void serverInitItemStackIds() = 0;
	virtual std::vector<ItemStack> getItemCopies() = 0;
	virtual void setSlot(int32_t slot, const ItemStack& stack, bool fromNetwork) = 0;
	virtual const ItemStack& getSlot(int32_t slot) = 0;
	virtual void setData(int32_t id, int32_t value) = 0;
	virtual void broadcastChanges() = 0;
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