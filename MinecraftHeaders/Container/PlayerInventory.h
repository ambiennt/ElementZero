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
	int32_t selectedSlot = 0;
	ItemStack item;
	ContainerID selectedContainerId = ContainerID::Inventory;
	std::unique_ptr<Inventory> inventory;
	std::vector<ItemStack> complexItems;
	std::weak_ptr<HudContainerManagerModel> model;

	struct SlotData {
		ContainerID mContainerId;
		int32_t mSlot;
	};

	MCAPI void ContainerSizeChanged(int) override;
	MCAPI void ContainerContentChanged(int) override;

	MCAPI void createTransactionContext(
			std::function<void(Container &, int, const ItemStack &, const ItemStack &)>, std::function<void()>);
};