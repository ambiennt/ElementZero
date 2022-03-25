#pragma once

#include "../Math/Vec3.h"
#include "../dll.h"

struct StateVectorComponent {
	Vec3 mPos;
	Vec3 mPosPrev;
	Vec3 mPosDelta;

	StateVectorComponent &operator=(StateVectorComponent const &rhs) {
		this->mPos = rhs.mPos;
		this->mPosPrev = rhs.mPosPrev;
		this->mPosDelta = rhs.mPosDelta;
		return *this;
	}
};

static_assert(sizeof(StateVectorComponent) == 0x24);