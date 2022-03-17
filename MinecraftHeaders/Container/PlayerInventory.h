#pragma once

#include "ContainerContentChangeListener.h"
#include "ContainerSizeChangeListener.h"
#include "../Core/ContainerID.h"
#include "Inventory.h"
#include "../dll.h"

#include <memory>

class HudContainerManagerModel;

class PlayerInventory : public ContainerSizeChangeListener, public ContainerContentChangeListener {
public:
	int32_t mSelectedSlot = 0; // mSelected
	ItemStack mInfiniteItem;
	ContainerID mSelectedContainerId = ContainerID::Inventory;
	std::unique_ptr<Inventory> mInventory;
	std::vector<ItemStack> mComplexItems;
	std::weak_ptr<HudContainerManagerModel> mHudContainerManager;

	struct SlotData {
		ContainerID mContainerId;
		int32_t mSlot;
	};

	MCAPI void ContainerSizeChanged(int) override;
	MCAPI void ContainerContentChanged(int) override;

	MCAPI void createTransactionContext(
			std::function<void(Container &, int, const ItemStack &, const ItemStack &)>, std::function<void()>);
};