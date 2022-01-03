#pragma once

#include "../BlockActor/BlockActor.h"

class RandomizableBlockActorContainerBase : public BlockActor {
public:
	std::string mLootTable; // 0xD0
	int32_t mLootTableSeed; // 0xF0

	virtual ~RandomizableBlockActorContainerBase(void);
	virtual void load(class Level&, class CompoundTag const&, class DataLoadHelper&) override;
	virtual bool save(class CompoundTag&) const override;
};

static_assert(offsetof(RandomizableBlockActorContainerBase, mLootTable) == 0xD0);
static_assert(offsetof(RandomizableBlockActorContainerBase, mLootTableSeed) == 0xF0);

static_assert(sizeof(RandomizableBlockActorContainerBase) == 0xF8);