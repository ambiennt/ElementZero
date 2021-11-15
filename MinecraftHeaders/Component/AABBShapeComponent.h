#pragma once

#include "../dll.h"
#include "../Math/AABB.h"
#include "../Math/Vec2.h"

class AABBShapeComponent {
public:
	AABB mAABB;
	Vec2 mBBDim;
};