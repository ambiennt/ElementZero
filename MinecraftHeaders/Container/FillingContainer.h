#pragma once

#include "Container.h"
#include "ContainerType.h"

#include "../dll.h"
#include <memory>

class Level;
class SemVersion;

class FillingContainer : public Container {
public:
	std::vector<ItemStack> mItems; // 0xE0
	Player *mPlayer; // 0xF8

	MCAPI FillingContainer(Player *, int, ContainerType);

	virtual bool add(ItemStack &);
	virtual bool canAdd(ItemStack const &);
	virtual void dropAll(bool);
	virtual void clearSlot(int);
	virtual void clearInventory(int);
	virtual void load(ListTag const &, SemVersion const &, Level &);
	virtual void doDrop(ItemStack &, bool);
	virtual int getEmptySlotsCount() const;
	virtual void dropAll(int, int, bool);

	MCAPI std::unique_ptr<ListTag> save();
};

static_assert(offsetof(FillingContainer, mItems) == 0xE0);
static_assert(offsetof(FillingContainer, mPlayer) == 0xF8);