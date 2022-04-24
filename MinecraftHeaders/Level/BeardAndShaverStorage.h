#pragma once

#include <shared_mutex>
#include <vector>
#include <unordered_map>
#include "../Math/ChunkPos.h"
#include "../Math/BoundingBox.h"

struct BeardAndShaverDescription {
	BoundingBox mCachedPieceBounds;
	int32_t mCachedPieceBaseY;
	int32_t mCachedXCenter;
	int32_t mCachedZCenter;
	float mCachedMaxRadius;
	int32_t mDeltaTargetY;
	BoundingBox mBoundingBox;
	float mMinBeardWidth;
	float mMaxBeardWidth;
};

class BeardAndShaverStorage {
	std::unordered_map<ChunkPos, std::vector<BeardAndShaverDescription>> mBeardsAndShaversToProcess;
	std::shared_mutex mMutex;
};