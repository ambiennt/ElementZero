#pragma once

#include "../dll.h"
#include "Vec3.h"

class AABB {
public:
	Vec3 min,
	Vec3 max,
	bool empty
};

static_assert(sizeof(AABB) == 0x1C);