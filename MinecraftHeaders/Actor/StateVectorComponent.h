#pragma once

#include "../Math/Vec3.h"
#include "../dll.h"

struct StateVectorComponent {
	Vec3 mPos;
	Vec3 mPosPrev;
	Vec3 mPosDelta;

	StateVectorComponent &operator=(StateVectorComponent const&) = default;
};

static_assert(sizeof(StateVectorComponent) == 0x24);