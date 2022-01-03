#pragma once

#include "Container.h"
#include "../Item/ItemStack.h"

class CraftingContainer : public Container {
public:
	std::vector<ItemStack> mItems; // 0xE0
	int32_t mWidth; // 0xF8

};

static_assert(offsetof(CraftingContainer, mItems) == 0xE0);
static_assert(offsetof(RandomizableBlockActorContainerBase, mWidth) == 0xF8);