#pragma once

#include "Tick.h"
#include "../Core/SpinLock.h"
#include "ChunkState.h"
#include "DirtyTicksCounter.h"
#include "../Math/BlockPos.h"
#include "../Math/BoundingBox.h"
#include "../Block/Brightness.h"
#include "../dll.h"
#include <modutils.h>

#include <cstdint>
#include <thread>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <vector>
#include <array>

enum class ChunkCachedDataState : int8_t {
	NotGenerating = 0,
	Generating    = 1,
	Generated     = 2
};

enum class ChunkDebugDisplaySavedState : int8_t {
	Generated = 0,
	Saved     = 1
};

enum class LevelChunkFormat : int8_t {
	v9_00 = 0x0,
	v9_02 = 0x1,
	v9_05 = 0x2,
	v17_0 = 0x3,
	v18_0 = 0x4,
	vConsole1_to_v18_0 = 0x5,
	v1_2_0 = 0x6,
	v1_2_0_bis = 0x7,
	v1_3_0 = 0x8,
	v1_8_0 = 0x9,
	v1_9_0 = 0xA,
	v1_10_0 = 0xB,
	v1_11_0 = 0xC,
	v1_11_1 = 0xD,
	v1_11_2 = 0xE,
	v1_12_0 = 0xF,
	v1_14_0 = 0x10,
	v1_15_0 = 0x11,
	v1_16_0 = 0x12,
	v1_16_0_bis = 0x13,
	Count_3 = 0x14,
};

enum class ChunkTerrainDataState : int8_t {
	NoData_0           = 0x0,
	NeedsFixup         = 0x1,
	ReadyForGeneration = 0x2,
	Generated_0        = 0x3,
	PostProcessed_0    = 0x4,
	Ready              = 0x5,
};

struct BiomeChunkState {
	uint8_t mSnowLevel; // 0x0
};

struct BiomeChunkData {
	uint8_t mBiome; // 0x0
};

struct ColumnCachedData {
	int32_t mGrassColor; // 0x0
	int32_t mWaterColor; // 0x4
};

class LevelChunk {
public:

	class HardcodedSpawningArea {
	public:
		enum class HardcodedSpawnAreaType : int8_t {
			None		   = -1,
			NetherFortress	 = 0,
			WitchHut	       = 1,
			OceanMonument	  = 2,
			Village_Deprecated     = 3,
			PillagerOutpost	= 4,
			NewVillage_Deprecated  = 5,
			Count		  = 6
		};

		BoundingBox mAABB;
		HardcodedSpawnAreaType mType;
	};

	enum class Finalization {
		Requeue = 0,
		Done    = 1,
		Noop    = 2
	};

	CLASS_FIELD(mLevel, 0x0, class Level *);
	CLASS_FIELD(mDimension, 0x8, class Dimension *);
	CLASS_FIELD(mMin, 0x10, class BlockPos);
	CLASS_FIELD(mMax, 0x1C, class BlockPos);
	CLASS_FIELD(mPosition, 0x28, class ChunkPos);
	CLASS_FIELD(mLightingFixupDone, 0x30, std::atomic<bool>);
	CLASS_FIELD(mReadOnly, 0x32, bool);
	CLASS_FIELD(mGenerator, 0x38, class ChunkSource *);
	CLASS_FIELD(mLoadedFormat, 0x40, enum class LevelChunkFormat);
	CLASS_FIELD(mSerializedEntitiesBuffer, 0x48, std::string);
	CLASS_FIELD(mLoadState, 0x68, std::atomic<enum ChunkState>);
	CLASS_FIELD(mTerrainDataState, 0x69, enum class ChunkTerrainDataState);
	CLASS_FIELD(mDebugDisplaySavedState, 0x6A, enum ChunkDebugDisplaySavedState);
	CLASS_FIELD(mCachedDataState, 0x6B, enum ChunkCachedDataState);
	CLASS_FIELD(mCachedDataStateSpinLock, 0x70, class SpinLock);
	CLASS_FIELD(mLastTick, 0x90, struct Tick);
	CLASS_FIELD(mTickQueue, 0x98, std::unique_ptr<class BlockTickingQueue>);
	CLASS_FIELD(mRandomTickQueue, 0xA0, std::unique_ptr<class BlockTickingQueue>);
	//CLASS_FIELD(mSubChunks, 0xA8, struct AppendOnlyAtomicLookupTable<class SubChunk, 16>);
	CLASS_FIELD(mSubChunkSpinLocks, 0x450, std::array<class SpinLock, 16>);
	CLASS_FIELD(mBiomes, 0x650, std::array<struct BiomeChunkData, 256>);
	CLASS_FIELD(mCachedData, 0x750, std::array<struct ColumnCachedData, 256>);
	CLASS_FIELD(mHeightmap, 0xF50, std::array<int16_t, 256>);
	CLASS_FIELD(mPreWorldGenHeightmap, 0x1150, std::unique_ptr<std::vector<int16_t>>);
	CLASS_FIELD(mBiomeStates, 0x1158, std::unordered_map<uint8_t, struct BiomeChunkState>);
	CLASS_FIELD(mHasCachedTemperatureNoise, 0x1198, bool);
	CLASS_FIELD(mBorderBlockMap, 0x1199, std::array<uint8_t, 256>);
	CLASS_FIELD(mFinalized, 0x129C, enum LevelChunk::Finalization);
	CLASS_FIELD(mIsRedstoneLoaded, 0x12A0, bool);
	CLASS_FIELD(mOwnedByTickingThread, 0x12A1, bool);
	CLASS_FIELD(mFullChunkDirtyTicksCounters, 0x12A4, class DirtyTicksCounter);
	CLASS_FIELD(mRainHeights, 0x12D4, std::array<int16_t, 256>);
	//CLASS_FIELD(mEntities, 0x14D8, SmallSet<std::unique_ptr<class Actor>>);
	CLASS_FIELD(mBlockEntities, 0x14F0, std::unordered_map<class ChunkBlockPos, std::shared_ptr<class BlockActor>>);
	CLASS_FIELD(mDeletedBlockEntities, 0x1530, std::vector<std::shared_ptr<class BlockActor>>);
	CLASS_FIELD(mDefaultBrightness, 0x1548, struct BrightnessPair);
	CLASS_FIELD(mHardcodedSpawningAreas, 0x1550, std::vector<class LevelChunk::HardcodedSpawningArea>);
	CLASS_FIELD(mbChunkInterpolants, 0x1568, std::array<std::array<uint8_t, 2>, 2>); // actually a 2d c array
	CLASS_FIELD(mbChunkHasConverterTag, 0x156C, bool);
	CLASS_FIELD(mDBChunkSurroundedByNeighbors, 0x156D, bool);
	CLASS_FIELD(mLevelChunkChecksums, 0x1570, std::unordered_map<class LevelChunkHashMapKey, uint64_t>);
	CLASS_FIELD(mOnChunkLoadedCalled, 0x15B0, bool);
	CLASS_FIELD(mBlockEntityAccessThread, 0x15B4, std::thread::id);
	CLASS_FIELD(mBlockEntityAccessThreadMutex, 0x15B8, std::mutex);
	CLASS_FIELD(mBlockEntityAccessCount, 0x1608, uint32_t);

	MCAPI void setSaved();
	MCAPI void setUnsaved();
	MCAPI bool hasEntity(class Actor&);
};

class LevelChunkGarbageCollector {
public:
	Dimension *mDimension; // 0x0
	uint8_t mLevelChunksToDiscard[0x268]; // MPMCQueue<std::unique_ptr<LevelChunk, LevelChunkFinalDeleter>> - 0x8
	std::atomic<uint64_t> mPendingDeletes; // 0x270
};

static_assert(sizeof(LevelChunkGarbageCollector) == 0x278);