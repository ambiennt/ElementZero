#pragma once

#include "../dll.h"
#include "../Actor/Player.h"
#include "../Item/ItemStack.h"
#include "ContainerManager.h"
#include "../Core/ContainerID.h"
#include "../Container/ContainerType.h"
#include "../Container/Container.h"

class BaseContainerMenu : public ContainerContentChangeListener, public IContainerManager {
public:
	Player *mPlayer; // 0x10
	std::vector<ItemStack> mLastSlots; // 0x18
	ContainerID mContainerId; // 0x30
	ContainerType mContainerType; // 0x31
};
static_assert(offsetof(BaseContainerMenu, mPlayer) == 0x10);
static_assert(offsetof(BaseContainerMenu, mLastSlots) == 0x18);
static_assert(offsetof(BaseContainerMenu, mContainerId) == 0x30);
static_assert(offsetof(BaseContainerMenu, mContainerType) == 0x31);
static_assert(sizeof(BaseContainerMenu) == 0x38);

class InventoryMenu : public BaseContainerMenu {
public:
	Container *mContainer; // 0x38
};

static_assert(offsetof(InventoryMenu, mContainer) == 0x38);
static_assert(sizeof(InventoryMenu) == 0x40);