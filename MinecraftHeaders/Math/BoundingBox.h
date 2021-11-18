#pragma once

#include "../dll.h"
#include "BlockPos.h"

class BoundingBox {
public:
	BlockPos min;
	BlockPos max;
};