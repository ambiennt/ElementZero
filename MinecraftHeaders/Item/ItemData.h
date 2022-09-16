#pragma once

#include "../Core/HashedString.h"
#include "../dll.h"
#include <cstdint>

struct ItemData {
    HashedString mName;
    int16_t mId;
};
static_assert(sizeof(ItemData) == 0x30);