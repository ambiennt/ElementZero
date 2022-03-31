#pragma once

#include "../Core/NBT.h"
#include "../Core/WeakPtr.h"
#include "BlockLegacy.h"
#include "../dll.h"

#include <modutils.h>

class Block {

public:

	uint16_t mAux; // const uint16_t mData - 0x8
	WeakPtr<BlockLegacy> mLegacyBlock; // 0x10
	CompoundTag mSerializationId; // 0x18
	uint32_t mRuntimeId; // 0x30
	bool mHasRuntimeId; // 0x34

	MCAPI virtual ~Block();
	MCAPI virtual enum BlockRenderLayer getRenderLayer() const;

	template <typename T> MCAPI class Block const *setState(class ItemState const &, T) const;
	template <typename T> MCAPI T getState(class ItemState const &) const;

	MCAPI bool isSlabBlock(void) const;
	MCAPI bool isSolidBlockingBlock(void) const;
	MCAPI bool hasState(class ItemState const &) const;
	MCAPI class Block const &keepState(class ItemState const &) const;
	MCAPI class BlockLegacy const &getLegacyBlock(void) const;
	MCAPI class Block const &copyState(class Block const &, class ItemState const &) const;
	MCAPI bool isSolidBlockingBlockAndNotSignalSource(void) const;
	MCAPI void spawnResources(class BlockSource &, class BlockPos const &, float, int) const;
	MCAPI std::string toDebugString(void) const;
	MCAPI unsigned int getStateMask(class ItemState const &) const;
};

static_assert(offsetof(Block, mAux) == 0x8);
static_assert(offsetof(Block, mLegacyBlock) == 0x10);
static_assert(offsetof(Block, mSerializationId) == 0x18);
static_assert(offsetof(Block, mRuntimeId) == 0x30);
static_assert(offsetof(Block, mHasRuntimeId) == 0x34);