#pragma once

#include "Enchant.h"
#include "../dll.h"

enum class EnchantResultType : char {
    Fail      = 0,
    Conflict  = 1,
    Increment = 2,
    Enchant   = 3
};

struct EnchantResult {
    EnchantResultType result;
    size_t enchantIdx;
    int level;
};

static_assert(offsetof(EnchantResult, enchantIdx) == 0x8);
static_assert(offsetof(EnchantResult, level) == 0x10);
static_assert(sizeof(EnchantResult) == 0x18);