#pragma once

#include "ContainerContentChangeListener.h"
#include "ContainerSizeChangeListener.h"
#include "ContainerID.h"
#include "Inventory.h"
#include "../dll.h"

class HudContainerManagerModel;

class PlayerInventory : public ContainerSizeChangeListener, public ContainerContentChangeListener {
public:
	int32_t mSelectedSlot; // mSelected
	ItemStack mInfiniteItem;
	ContainerID mSelectedContainerId;
	std::unique_ptr<Inventory> mInventory;
	std::vector<ItemStack> mComplexItems;
	std::weak_ptr<HudContainerManagerModel> mHudContainerManager;

	struct SlotData {
		ContainerID mContainerId;
		int32_t mSlot;
	};

	virtual void createTransactionContext(
		std::function<void(Container &, int32_t, const ItemStack &, const ItemStack &)>, std::function<void()>);

	inline int32_t getContainerSize() const {
		return this->mInventory->getContainerSize();
	}
};