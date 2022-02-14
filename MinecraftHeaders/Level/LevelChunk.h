#pragma once

#include "Level.h"
#include "Dimension.h"
#include "Tick.h"
#include "../Core/SpinLock.h"
#include "SubChunk.h"
#include "ChunkState.h"
#include "DirtyTicksCounter.h"
#include "../Math/BlockPos.h"
#include "../Math/BoundingBox.h"
#include "../Block/Brightness.h"
#include "../dll.h"
#include <modutils.h>

#include <thread>
#include <mutex>
#include <atomic>

enum class ChunkCachedDataState : int8_t {
	NotGenerating = 0,
	Generating    = 1,
	Generated     = 2
};

enum class ChunkDebugDisplaySavedState : int8_t {
	Generated = 0,
	Saved     = 1
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
			None                   = -1,
			NetherFortress         = 0,
			WitchHut               = 1,
			OceanMonument          = 2,
			Village_Deprecated     = 3,
			PillagerOutpost        = 4,
			NewVillage_Deprecated  = 5,
			Count                  = 6
		};

		BoundingBox mAABB;
		HardcodedSpawnAreaType mType;
	};

	enum class Finalization {
		Requeue = 0,
		Done    = 1,
		Noop    = 2
	};

	BUILD_ACCESS_MUT(class Level *, mLevel, 0x0);
	BUILD_ACCESS_MUT(class Dimension *, mDimension, 0x8);
	BUILD_ACCESS_MUT(class BlockPos, mMin, 0x10);
	BUILD_ACCESS_MUT(class BlockPos, mMax, 0x1C);
	BUILD_ACCESS_MUT(class ChunkPos, mPosition, 0x28);
	BUILD_ACCESS_MUT(std::atomic<bool>, mLightingFixupDone, 0x30);
	BUILD_ACCESS_MUT(bool, mReadOnly, 0x32);
	BUILD_ACCESS_MUT(class ChunkSource *, mGenerator, 0x38);
	BUILD_ACCESS_MUT(uint8_t, mLoadedFormat, 0x40); // char array of size 1
	BUILD_ACCESS_MUT(std::string, mSerializedEntitiesBuffer, 0x48);
	BUILD_ACCESS_MUT(std::atomic<enum ChunkState>, mLoadState, 0x68);
	BUILD_ACCESS_MUT(int8_t, mTerrainDataState, 0x69); // char array of size 1
	BUILD_ACCESS_MUT(enum ChunkDebugDisplaySavedState, mDebugDisplaySavedState, 0x6A);
	BUILD_ACCESS_MUT(enum ChunkCachedDataState, mCachedDataState, 0x6B);
	BUILD_ACCESS_MUT(class SpinLock, mCachedDataStateSpinLock, 0x70);
	BUILD_ACCESS_MUT(struct Tick, mLastTick, 0x90);
	BUILD_ACCESS_MUT(std::unique_ptr<class BlockTickingQueue>, mTickQueue, 0x98);
	BUILD_ACCESS_MUT(std::unique_ptr<class BlockTickingQueue>, mRandomTickQueue, 0xA0);

	//using lookupTable16 = struct AppendOnlyAtomicLookupTable<class SubChunk, 16>;
	//BUILD_ACCESS_MUT(lookupTable16, mSubChunks, 0xA8);

	using spinLockArr16 = std::array<class SpinLock, 16>;
	BUILD_ACCESS_MUT(spinLockArr16, mSubChunkSpinLocks, 0x450);

	using biomeChunkDataArr256 = std::array<struct BiomeChunkData, 256>;
	BUILD_ACCESS_MUT(biomeChunkDataArr256, mBiomes, 0x650);

	using ColumnCachedDataArr256 = std::array<struct ColumnCachedData, 256>;
	BUILD_ACCESS_MUT(ColumnCachedDataArr256, mCachedData, 0x750);

	using heightMapArr256 = std::array<int16_t, 256>;
	BUILD_ACCESS_MUT(heightMapArr256, mHeightmap, 0xF50);

	BUILD_ACCESS_MUT(std::unique_ptr<std::vector<int16_t>>, mPreWorldGenHeightmap, 0x1150);

	using biomeChunkStateMap = std::unordered_map<uint8_t, struct BiomeChunkState>;
	BUILD_ACCESS_MUT(biomeChunkStateMap, mBiomeStates, 0x1158);

	BUILD_ACCESS_MUT(bool, mHasCachedTemperatureNoise, 0x1198);

	using borderBlockMapArr256 = std::array<uint8_t, 256>;
	BUILD_ACCESS_MUT(borderBlockMapArr256, mBorderBlockMap, 0x1199);

	BUILD_ACCESS_MUT(enum LevelChunk::Finalization, mFinalized, 0x129C);
	BUILD_ACCESS_MUT(bool, mIsRedstoneLoaded, 0x12A0);
	BUILD_ACCESS_MUT(bool, mOwnedByTickingThread, 0x12A1);
	BUILD_ACCESS_MUT(class DirtyTicksCounter, mFullChunkDirtyTicksCounters, 0x12A4);

	using rainHeightsArr256 = std::array<int16_t, 256>;
	BUILD_ACCESS_MUT(rainHeightsArr256, mRainHeights, 0x12D4);

	BUILD_ACCESS_MUT(std::vector<std::unique_ptr<class Actor>>, mEntities, 0x14D8); // SmallSet<std::unique_ptr<Actor>> - I have no idea what a smallSet is

	using chunkBlockPosBlockActorMap = std::unordered_map<class ChunkBlockPos, std::shared_ptr<class BlockActor>>;
	BUILD_ACCESS_MUT(chunkBlockPosBlockActorMap, mBlockEntities, 0x14F0);

	BUILD_ACCESS_MUT(std::vector<std::shared_ptr<class BlockActor>>, mDeletedBlockEntities, 0x1530);
	BUILD_ACCESS_MUT(struct BrightnessPair, mDefaultBrightness, 0x1548);
	BUILD_ACCESS_MUT(std::vector<class LevelChunk::HardcodedSpawningArea>, mHardcodedSpawningAreas, 0x1550);

	using chunkInterpolantsArr2_2 = uint8_t[2][2];
	BUILD_ACCESS_MUT(chunkInterpolantsArr2_2, mbChunkInterpolants, 0x1568);

	BUILD_ACCESS_MUT(bool, mbChunkHasConverterTag, 0x156C);
	BUILD_ACCESS_MUT(bool, mDBChunkSurroundedByNeighbors, 0x156D);

	using levelChunkHashMap = std::unordered_map<class LevelChunkHashMapKey, uint64_t>;
	BUILD_ACCESS_MUT(levelChunkHashMap, mLevelChunkChecksums, 0x1570);

	BUILD_ACCESS_MUT(bool, mOnChunkLoadedCalled, 0x15B0);
	BUILD_ACCESS_MUT(std::thread::id, mBlockEntityAccessThread, 0x15B4);
	BUILD_ACCESS_MUT(std::mutex, mBlockEntityAccessThreadMutex, 0x15B8);
	BUILD_ACCESS_MUT(uint32_t, mBlockEntityAccessCount, 0x1608);

	MCAPI void setSaved(void);
	MCAPI void setUnsaved(void);
	MCAPI bool hasEntity(class Actor&);
};