#pragma once

#include "../dll.h"
#include "Item.h"
#include "../Block/Block.h"
#include "../Core/WeakPtr.h"

#include <modutils.h>

class ItemDescriptor {
public:
	CLASS_FIELD(mItem, 0x0, class WeakPtr<class Item>);
	CLASS_FIELD(mBlock, 0x8, const class Block*);
	CLASS_FIELD(mAuxValue, 0x10, int16_t);
	CLASS_FIELD(mValid, 0x12, bool);
};