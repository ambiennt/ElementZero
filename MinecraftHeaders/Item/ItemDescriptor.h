#pragma once

#include "../dll.h"
#include "Item.h"
#include "../Block/Block.h"
#include "../Core/WeakPtr.h"

#include <modutils.h>

#include <memory>

class ItemDescriptor {
public:
	BUILD_ACCESS_MUT(class WeakPtr<class Item>, mItem, 0x0);
	BUILD_ACCESS_MUT(const class Block*, mBlock, 0x8);
	BUILD_ACCESS_MUT(int16_t, mAuxValue, 0x10);
	BUILD_ACCESS_MUT(bool, mValid, 0x12);
};