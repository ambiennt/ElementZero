#pragma once

#include "ItemStack.h"
#include "../dll.h"

class ItemInstance : public ItemStackBase {
public:
    ItemInstance(Item const &item);
    ItemInstance(Item const &item, int);
    ItemInstance(Item const &item, int, int);
    ItemInstance(BlockLegacy const &, int);

    virtual void reinit(Item const &, int, int);
    virtual void reinit(BlockLegacy const &, int);
};