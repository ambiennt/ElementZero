#pragma once

#include <functional>

struct ResourcePacksInfoData {
  bool mTexturePackRequired;
  bool mHasScripts;
  bool mHasExceptions;
  char pad[0x35];
};

static_assert(offsetof(ResourcePacksInfoData, mHasExceptions) == 0x2);
static_assert(sizeof(ResourcePacksInfoData) == 0x38);