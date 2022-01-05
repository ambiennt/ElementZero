#pragma once

#include "Enchant.h"
#include "../dll.h"

enum class EnchantResultType : int8_t {
	Fail      = 0,
	Conflict  = 1,
	Increment = 2,
	Enchant   = 3
};

struct EnchantResult {
	EnchantResultType result; // 0x0
	uint64_t enchantIdx; // 0x8
	int32_t level; // 0x10
};

static_assert(offsetof(EnchantResult, enchantIdx) == 0x8);
static_assert(offsetof(EnchantResult, level) == 0x10);
static_assert(sizeof(EnchantResult) == 0x18);