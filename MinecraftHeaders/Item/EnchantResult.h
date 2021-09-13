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
  size_t EnchantIdx;
  int level;
};

static_assert(sizeof(EnchantResult) == 24);