#pragma once

#include "Container.h"
#include "../dll.h"

class SimpleContainer : public Container {
public:

	int32_t mSize; // 0xE0
	std::vector<ItemStack> mItems; // 0xE8

	MCAPI SimpleContainer(std::string const &, bool, int);
};

static_assert(offsetof(SimpleContainer, mSize) == 0xE0);
static_assert(offsetof(SimpleContainer, mItems) == 0xE8);