#pragma once

#include "ItemStack.h"
#include "../Core/NBT.h"
#include "../Block/Block.h"
#include "../Block/BlockLegacy.h"
#include "../dll.h"

class ItemInstance : public ItemStackBase {
public:

	virtual void reinit(BlockLegacy const& blockLegacy, int32_t count) override;
	virtual void reinit(Item const&, int32_t count, int32_t auxValue) override;
	
	ItemInstance() : ItemStackBase() {}
	// no symbols for these
	//MCAPI ItemInstance();
	//MCAPI ItemInstance(BlockLegacy const&, int32_t count, int16_t auxValue);
	//MCAPI ItemInstance(Item const &item, int32_t count, int32_t auxValue, CompoundTag const* userData);
	MCAPI ItemInstance(ItemStackBase const &rhs);
	MCAPI ItemInstance(ItemInstance const& rhs);
	MCAPI ItemInstance(Block const& block, int32_t count, CompoundTag const* userData);
	MCAPI ItemInstance(BlockLegacy const& blockLegacy, int32_t count);
	MCAPI ItemInstance(Item const &item);
	MCAPI ItemInstance(Item const &item, int32_t count);
	MCAPI ItemInstance(Item const &item, int32_t count, int32_t auxValue);
};