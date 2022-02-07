#pragma once

#include "../dll.h"
#include "DirtyTicksCounter.h"
#include "../Core/SpinLock.h"

#include <unordered_map>
#include <memory>
#include <functional>

class SubChunkBrightnessStorage;

class SubChunkBlockStorage {

	enum class Type	: int8_t {
		Paletted1 = 0x1,
		Paletted2 = 0x2,
		Paletted3 = 0x3,
		Paletted4 = 0x4,
		Paletted5 = 0x5,
		Paletted6 = 0x6,
		Paletted8 = 0x8,
		Paletted16 = 0x10,
	};

	virtual ~SubChunkBlockStorage();
	virtual bool isUniform(void) = 0;
	virtual const class Block* getBlock(uint16_t index) = 0;
	virtual void setBlock(uint16_t index, uint16_t pid) = 0;
	virtual void getBlockTypeCapacity()  = 0;
	virtual void getType(void) = 0;
	virtual std::unique_ptr<SubChunkBlockStorage> makePrunedCopy(void) = 0;
	virtual class ISubChunkBlockStoragePaletted* asPalettedStorage(void);
	virtual const class ISubChunkBlockStoragePaletted* asPalettedStorage(void) const;
	virtual void fetchBlocksInCylinder(
		class BlockPos const &positionOfChunk, class BlockPos const &pos, uint32_t radius, uint32_t height,
		std::function<bool (class Block const &)> const &predicate, std::vector<class BlockFetchResult> &output) = 0;
	virtual void fetchBlocksInBox(
		class BlockPos const &positionOfChunk, const class BoundingBox &box,
		std::function<bool (class Block const &)> const &predicate, std::vector<class BlockFetchResult> &output) = 0;
	virtual void _serialize(class IDataOutput &stream, bool network) = 0;
};

static_assert(sizeof(SubChunkBlockStorage) == 0x8);

class SubChunk {
public:
	DirtyTicksCounter mDirtyTicksCounter; // 0x0
	std::unique_ptr<SubChunkBrightnessStorage> mLight; // 0x8
	std::unique_ptr<SubChunkBlockStorage> mBlocks[2]; // 0x10
	SubChunkBlockStorage* mBlocksReadPtr[2]; // 0x20
 	SpinLock* mWriteLock; // 0x30
};

static_assert(offsetof(SubChunk, mLight) == 0x8);
static_assert(offsetof(SubChunk, mBlocks) == 0x10);
static_assert(offsetof(SubChunk, mBlocksReadPtr) == 0x20);
static_assert(offsetof(SubChunk, mWriteLock) == 0x30);