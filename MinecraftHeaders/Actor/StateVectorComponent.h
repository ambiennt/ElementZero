#pragma once

#include "../Math/Vec3.h"
#include "../dll.h"

struct StateVectorComponent {
	Vec3 mPos;
	Vec3 mPosPrev;
	Vec3 mPosDelta; 
};

static_assert(sizeof(StateVectorComponent) == 0x24);