#pragma once

#include "../Core/WeakPtr.h"
#include "../Core/NBT.h"
#include "BlockLegacy.h"
#include "../dll.h"

#include <modutils.h>

class Block {

public:

	BUILD_ACCESS_MUT(const uint16_t, mAux, 0x8); // mData
	BUILD_ACCESS_MUT(class WeakPtr<class BlockLegacy>, mLegacyBlock, 0x10);
	BUILD_ACCESS_MUT(class CompoundTag, mSerializationId, 0x18);
	BUILD_ACCESS_MUT(uint32_t, mRuntimeId, 0x30);
	BUILD_ACCESS_MUT(bool, mHasRuntimeId, 0x34);

	MCAPI virtual ~Block();
	MCAPI virtual enum BlockRenderLayer getRenderLayer() const;

	
	template <typename T> MCAPI class Block const *setState(class ItemState const &, T) const;
	template <typename T> MCAPI T getState(class ItemState const &) const;
	MCAPI bool isSlabBlock(void) const;
	MCAPI bool isSolidBlockingBlock(void) const;
	MCAPI bool hasState(class ItemState const &) const;
	MCAPI class Block const &keepState(class ItemState const &) const;
	inline class BlockLegacy const &getLegacyBlock(void) const { return *mLegacyBlock; }
	MCAPI class Block const &copyState(class Block const &, class ItemState const &) const;
	MCAPI bool isSolidBlockingBlockAndNotSignalSource(void) const;
	MCAPI void spawnResources(class BlockSource &, class BlockPos const &, float, int) const;
	MCAPI std::string toDebugString(void) const;
	MCAPI unsigned int getStateMask(class ItemState const &) const;

	AS_FIELD(class BlockLegacy const &, LegacyBlock, getLegacyBlock);
};