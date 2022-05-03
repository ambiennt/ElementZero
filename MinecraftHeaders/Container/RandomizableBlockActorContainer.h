#pragma once

#include "../BlockActor/BlockActor.h"
#include "FillingContainer.h"

class RandomizableBlockActorContainerBase : public BlockActor {
public:
  std::string mLootTable; // 0xD0
  int32_t mLootTableSeed; // 0xF0
};

static_assert(offsetof(RandomizableBlockActorContainerBase, mLootTable) == 0xD0);
static_assert(offsetof(RandomizableBlockActorContainerBase, mLootTableSeed) == 0xF0);
static_assert(sizeof(RandomizableBlockActorContainerBase) == 0xF8);




class RandomizableBlockActorContainer : public RandomizableBlockActorContainerBase, public Container {
public:
};

class RandomizableBlockActorFillingContainer : public RandomizableBlockActorContainerBase, public FillingContainer {
public:
};