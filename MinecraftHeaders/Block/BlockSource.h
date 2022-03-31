#pragma once

#include <functional>

#include "../FakeGSL/span.h"
#include "../Core/buffer_span.h"
#include "../Actor/ActorType.h"
#include "../Block/ActorBlockSyncMessage.h"
#include "../Block/Block.h"
#include "../Math/ChunkPos.h"
#include "../Math/AABB.h"
#include "Brightness.h"
#include "BlockFetchResult.h"
#include "../dll.h"

#include <modutils.h>
#include <hook.h>
#include <thread>

class Level;
class LevelChunk;
class ChunkSource;
class Dimension;
class BlockSourceListener;
class BlockTickingQueue;

enum class ActorType;
enum class LegacyBlockID : uint16_t;
enum class MaterialType;

enum class TickingQueueType {
	Internal = 0,
	Random = 1
};

class BlockSource {
public:

	const std::thread::id mOwnerThreadID; // 0x8
	const bool mAllowUnpopulatedChunks; // 0xC
	const bool mPublicSource; // 0xD
	Level* mLevel; // 0x10
	ChunkSource* mChunkSource; // 0x18
	Dimension* mDimension; // 0x20
	const int16_t mMaxHeight; // 0x28
	std::vector<BlockFetchResult> mTempBlockFetchResult; // 0x30
	BlockPos mPlaceChunkPos; // 0x48
	std::vector<BlockSourceListener*> mListeners; // 0x58
	std::vector<BlockSourceListener*> mTestOnlyBlockChangeListeners; // 0x70
	std::unordered_map<BlockPos, int32_t> mTestOnlySetBlockRecursionLevel; // 0x88
	std::unordered_map<BlockPos, int32_t> mTestOnlySetExtraBlockRecursionLevel; // 0xC8
	ChunkPos mLastChunkPos; // 0x108
	LevelChunk* mLastChunk; // 0x110
	BlockTickingQueue* mRandomTickQueue; // 0x118
	BlockTickingQueue* mTickQueue; // 0x120
	const BrightnessPair mDefaultBrightness; // 0x128
	std::vector<Actor*> mTempEntityList; // 0x130
	std::vector<BlockActor*> mTempBlockEntityList; // 0x148
	std::vector<AABB> mTempCubeList; // 0x160

	MCAPI BlockSource(class Level &, class Dimension &, class ChunkSource &, bool, bool);
	MCAPI virtual ~BlockSource();

	MCAPI bool canSeeSky(int, int, int) const;
	MCAPI short getHeightmap(int, int);
	MCAPI bool isEmptyBlock(int, int, int);
	MCAPI bool isInWall(class Vec3 const &);
	MCAPI class Block const &getBlock(int, int, int) const;
	MCAPI bool hasChunksAt(class AABB const &) const;
	MCAPI bool hasBlock(class BlockPos const &) const;
	MCAPI bool canSeeSky(class BlockPos const &) const;
	MCAPI bool hasChunksAt(struct Bounds const &) const;
	MCAPI bool isSolidBlockingBlock(int, int, int) const;
	MCAPI bool setBlock(int, int, int, class Block const &, int);
	MCAPI void blockEvent(class BlockPos const &, int, int);
	MCAPI short getHeightmap(class BlockPos const &) const;
	MCAPI bool hasBorderBlock(class BlockPos);
	MCAPI bool removeBlock(class BlockPos const &);
	MCAPI float getBrightness(class BlockPos const &) const;
	MCAPI class Material const &getMaterial(int, int, int) const;
	MCAPI bool hasChunksAt(class BlockPos const &, class BlockPos const &) const;
	MCAPI bool hasChunksAt(class BlockPos const &, int) const;
	MCAPI bool containsAnyLiquid(class AABB const &);
	MCAPI bool containsFireBlock(class AABB const &);
	MCAPI void neighborChanged(class BlockPos const &, class BlockPos const &);
	MCAPI float getVisualLiquidHeight(class Vec3 const &);
	MCAPI bool setBlockNoUpdate(int, int, int, class Block const &);
	MCAPI void updateNeighborsAt(class BlockPos const &);
	MCAPI class Biome &getBiome(class BlockPos const &);
	MCAPI class Block const &getBlock(class BlockPos const &) const;
	MCAPI class BlockActor *getBlockEntity(int, int, int);
	MCAPI class HitResult clip(class Vec3 const &, class Vec3 const &, bool, bool, int, bool, bool);
	MCAPI float getSeenPercent(class Vec3 const &, class AABB const &);
	MCAPI bool isUnderWater(class Vec3 const &, class Block const &) const;
	MCAPI bool containsAnySolidBlocking(class AABB const &);
	MCAPI class Biome *tryGetBiome(class BlockPos const &) const;
	MCAPI void addListener(class BlockSourceListener &);
	MCAPI bool areChunksFullyLoaded(class BlockPos const &, int);
	MCAPI bool hasTickInPendingTicks(class BlockPos const &) const;
	MCAPI class LevelChunk *getChunk(class ChunkPos const &) const;
	MCAPI class Biome const &getConstBiome(class BlockPos const &) const;
	MCAPI class Block const &getExtraBlock(class BlockPos const &) const;
	MCAPI bool isConsideredSolidBlock(class BlockPos const &);
	MCAPI bool canSeeSkyFromBelowWater(class BlockPos const &);
	MCAPI void fireBlockEntityChanged(class BlockActor &);
	MCAPI short getAboveTopSolidBlock(class BlockPos const &, bool, bool);
	MCAPI class Block const &getLiquidBlock(class BlockPos const &) const;
	MCAPI bool setExtraBlock(class BlockPos const &, class Block const &, int);
	MCAPI bool containsLiquid(class AABB const &, enum MaterialType);
	MCAPI bool findNextTopSolidBlockAbove(class BlockPos &);
	MCAPI bool findNextTopSolidBlockUnder(class BlockPos &);
	MCAPI bool containsMaterial(class AABB const &, enum MaterialType);
	MCAPI class BlockActor *getBlockEntity(class BlockPos const &);
	MCAPI void addToTickingQueue(class BlockPos const &, class Block const &, int, int);
	MCAPI bool isUnobstructedByEntities(class AABB const &, class Actor *);
	MCAPI class AABB generateUnloadedChunkAABB(class ChunkPos const &);
	MCAPI struct Brightness getRawBrightness(class BlockPos const &, bool, bool) const;
	MCAPI bool isPositionUnderLiquid(class Vec3 const &, enum MaterialType);
	MCAPI bool mayPlace(class Block const &, class BlockPos const &, unsigned char, class Actor *, bool);
	MCAPI bool containsAnyBlockOfType(class BlockPos const &, class BlockPos const &, class Block const &);
	MCAPI struct BrightnessPair getBrightnessPair(class BlockPos const &) const;
	MCAPI bool isTouchingMaterial(class BlockPos const &, enum MaterialType) const;
	MCAPI void updateNeighborsAtExceptFromFacing(class BlockPos const &, class BlockPos const &, int);
	MCAPI void addToRandomTickingQueue(class BlockPos const &, class Block const &, int, int);
	MCAPI bool findNextSpawnBlockUnder(class BlockPos &, enum MaterialType);
	MCAPI bool hasTickInCurrentTick(class BlockPos const &, enum TickingQueueType) const;
	MCAPI bool hasTickInPendingTicks(class BlockPos const &, enum TickingQueueType) const;
	MCAPI bool setBlock(class BlockPos const &, class Block const &, int, struct ActorBlockSyncMessage const *);
	MCAPI class Actor *fetchNearestEntityOfType(class Actor *, class AABB const &, enum ActorType);
	MCAPI void fireBlockEntityAboutToBeRemoved(class std::shared_ptr<class BlockActor>);
	MCAPI bool checkBlockPermissions(class Actor &, class BlockPos const &, unsigned char, class ItemStack const &, bool);
	MCAPI bool getNextTickUpdateForPos(class BlockPos const &, enum TickingQueueType, struct Tick &) const;
	MCAPI bool checkBlockDestroyPermissions(class Actor &, class BlockPos const &, class ItemStack const &, bool);
	MCAPI void fireBlockChanged(
		class BlockPos const &, unsigned int, class Block const &, class Block const &, int, struct ActorBlockSyncMessage const *);
	MCAPI class Block const *isOnTopOfBlock(class AABB const &, std::function<bool(Block const &)>);
	MCAPI class std::vector<class AABB> &fetchAABBs(class AABB const &, bool);
	MCAPI class std::vector<class Actor *> const &fetchEntities(class Actor *, class AABB const &);
	MCAPI bool setBlock(
		class BlockPos const &, class Block const &, int, class std::shared_ptr<class BlockActor>, struct ActorBlockSyncMessage const *);
	MCAPI void fetchBlockEntities(class AABB const &, class std::vector<class BlockActor *> &);
	MCAPI class std::vector<class AABB> &fetchCollisionShapes(class AABB const &, float *, bool, class Actor *);
	MCAPI class std::vector<class Actor *> const &fetchEntities2(enum ActorType, class AABB const &, bool);
	MCAPI class std::vector<class Actor *> const &fetchEntities(enum ActorType, class AABB const &, class Actor *);
	MCAPI class std::vector<class Actor *> const &fetchEntities(class buffer_span<class Actor *>, class AABB const &);
	MCAPI class std::vector<class Actor *> const &fetchActors(struct ActorDefinitionIdentifier const &, class AABB const &);
	MCAPI class gsl::span<class BlockFetchResult const>fetchBlocksInBox(class BoundingBox const &, std::function<bool(Block const &)>);
	MCAPI class gsl::span<class BlockFetchResult const>
		fetchBlocksInCylinder(class BlockPos const &, unsigned int, unsigned int, std::function<bool(Block const &)>);
	MCAPI class gsl::span<class BlockFetchResult const>
		fetchBlocksInCylinderSorted(class BlockPos const &, unsigned int, unsigned int, std::function<bool(Block const &)>);

	enum LegacyBlockID getBlockIdAt(Vec3 const &pos) {
		return (LegacyBlockID)this->getBlock(BlockPos(pos)).mLegacyBlock->mId;
	}

	enum LegacyBlockID getBlockIdAt(BlockPos const &pos) {
		return (LegacyBlockID)this->getBlock(pos).mLegacyBlock->mId;
	}

	enum LegacyBlockID getBlockIdAt(int32_t x, int32_t y, int32_t z) {
		return (LegacyBlockID)this->getBlock(BlockPos(x, y, z)).mLegacyBlock->mId;
	}
};

static_assert(offsetof(BlockSource, mDimension) == 0x20);
static_assert(offsetof(BlockSource, mTempBlockFetchResult) == 0x30);
static_assert(offsetof(BlockSource, mTestOnlyBlockChangeListeners) == 0x70);
static_assert(offsetof(BlockSource, mLastChunk) == 0x110);
static_assert(offsetof(BlockSource, mTempEntityList) == 0x130);
static_assert(offsetof(BlockSource, mTempCubeList) == 0x160);
static_assert(sizeof(BlockSource) == 0x178);