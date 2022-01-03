#pragma once

#include "Container.h"

#include "../dll.h"

class SimpleContainer : public Container {
public:

	int32_t mSize; // 0xE0
	std::vector<ItemStack> mItems; // 0xE8

	MCAPI SimpleContainer(std::string const &, bool, int);
	MCAPI ~SimpleContainer() override;
	MCAPI virtual ItemStack const &getItem(int) const override;
	MCAPI virtual void setItem(int, ItemStack const &) override;
	MCAPI virtual int getContainerSize() const override;
	MCAPI virtual int getMaxStackSize() const override;
	MCAPI virtual void startOpen(Player &) override;
	MCAPI virtual void stopOpen(Player &) override;
};

static_assert(offsetof(SimpleContainer, mSize) == 0xE0);
static_assert(offsetof(SimpleContainer, mItems) == 0xE8);