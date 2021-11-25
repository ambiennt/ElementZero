#pragma once

#include "ItemStack.h"
#include "../Core/NBT.h"
#include "../Block/Block.h"
#include "../Block/BlockLegacy.h"
#include "../dll.h"

class ItemInstance : public ItemStackBase {
public:

    virtual void reinit(Item const&, int32_t count, int32_t auxValue);
    virtual void reinit(BlockLegacy const& blockLegacy, int32_t count);

    ItemInstance(BlockLegacy const&, int32_t count, int16_t auxValue);
    MCAPI ItemInstance(ItemInstance const&);
    MCAPI ItemInstance(Block const& block, int32_t count, CompoundTag const* userData);
    MCAPI ItemInstance(BlockLegacy const& blockLegacy, int32_t count);
    MCAPI ItemInstance(Item const &item);
    MCAPI ItemInstance(Item const &item, int32_t count);
    MCAPI ItemInstance(Item const &item, int32_t count, int32_t auxValue);
    ItemInstance(Item const &item, int32_t count, int32_t auxValue, CompoundTag const* userData);
    ItemInstance(const ItemStackBase &itemStack);
    ItemInstance();
};