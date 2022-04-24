#pragma once

#include <memory>

#include "../Core/AutomaticID.h"
#include "../Math/Vec3.h"

class Dimension;
class CompoundTag;
enum class DimensionID : int32_t;

class ChangeDimensionRequest {
public:

	enum class State {
		PrepareRegion     = 0,
		WaitingForChunks  = 1,
		WaitingForRespawn = 2
	};

	State mState = State::PrepareRegion;
	DimensionID mFromDimensionId, mToDimensionId; // AutomaticID<Dimension, int32_t>
	Vec3 mPos;
	bool mUsePortal, mRespawn;
	std::unique_ptr<CompoundTag> mAgentTag;
};