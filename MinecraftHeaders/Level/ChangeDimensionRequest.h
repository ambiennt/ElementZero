#pragma once

#include <memory>

#include "../Core/AutomaticID.h"
#include "../Core/NBT.h"
#include "../Math/Vec3.h"

class Dimension;

class ChangeDimensionRequest {
public:

	enum class State {
		PrepareRegion     = 0,
		WaitingForChunks  = 1,
		WaitingForRespawn = 2
	};

	State mState = State::PrepareRegion;
	AutomaticID<Dimension, int32_t> mFromDimensionId, mToDimensionId;
	Vec3 mPos;
	bool mUsePortal, mRespawn;
	std::unique_ptr<CompoundTag> mAgentTag;
};