#pragma once

#include "../Core/NBT.h"
#include "../Core/WeakPtr.h"
#include "BlockLegacy.h"
#include "../Item/VanillaStates.h"
#include "../dll.h"

enum class BlockRenderLayer : int32_t;
enum class CreativeItemCategory : int32_t;
class BlockPos;
class BlockSource;

class Block { // const class Block
public:

	uint16_t mAux; // const uint16_t mData - 0x8
	WeakPtr<BlockLegacy> mLegacyBlock; // 0x10
	CompoundTag mSerializationId; // 0x18
	uint32_t mRuntimeId; // 0x30
	bool mHasRuntimeId; // 0x34

	virtual ~Block();
	virtual BlockRenderLayer getRenderLayer() const;

	template <typename T> MCAPI Block const *setState(ItemState const &, T) const;
	template <typename T> MCAPI T getState(ItemState const &) const;
	MCAPI bool isSolidBlockingBlock() const;
	MCAPI bool hasState(ItemState const &) const;
	MCAPI Block const &keepState(ItemState const &) const;
	MCAPI BlockLegacy const &getLegacyBlock() const;
	MCAPI Block const &copyState(Block const &, ItemState const &) const;
	MCAPI bool isSolidBlockingBlockAndNotSignalSource() const;
	MCAPI void spawnResources(BlockSource &, BlockPos const &, float, int32_t) const;
	MCAPI std::string toDebugString() const;
	MCAPI uint32_t getStateMask(ItemState const &) const;
	MCAPI CreativeItemCategory getCreativeCategory() const;

	MCAPI static const std::string BLOCK_DESCRIPTION_PREFIX;

	inline bool operator==(const Block& rhs) const {
		return (this->mLegacyBlock.get() == rhs.mLegacyBlock.get()) && (this->mAux == rhs.mAux);
	}
	inline bool operator!=(const Block& rhs) const {
		return !(*this == rhs);
	}

	inline bool isWaterSource() const { // xref: BlockUtils::isWaterSource
		const auto& legacy = *this->mLegacyBlock.get();
		return ((legacy.getMaterialType() == MaterialType::Water) &&
				(legacy.mStates[VanillaStates::LiquidDepth.mID].mInitialized) &&
				(legacy.getState<int32_t>(VanillaStates::LiquidDepth, this->mAux) == 0));
	}
protected:
	MCAPI void buildSerializationId(uint32_t);
public:
};

static_assert(offsetof(Block, mAux) == 0x8);
static_assert(offsetof(Block, mLegacyBlock) == 0x10);
static_assert(offsetof(Block, mSerializationId) == 0x18);
static_assert(offsetof(Block, mRuntimeId) == 0x30);
static_assert(offsetof(Block, mHasRuntimeId) == 0x34);
static_assert(sizeof(Block) == 0x38);