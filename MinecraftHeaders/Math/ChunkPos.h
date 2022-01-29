#pragma once

#include "Vec3.h"
#include "BlockPos.h"
#include "../dll.h"

class ChunkPos {
public:
	int32_t x = 0, z = 0;

	static ChunkPos ZERO;

	ChunkPos();
	inline ~ChunkPos() {}
	ChunkPos(int32_t x, int32_t z) : x(x), z(z) {}
	ChunkPos(BlockPos const& bp) : x((int)(bp.x % 16)), z((int)(bp.z % 16)) {}
    ChunkPos(const ChunkPos &rhs) {
		this->x = rhs.x;
		this->z = rhs.z;
	}
	ChunkPos(Vec3 const& vec) {
		BlockPos bp(vec);
		this->x = (int)(bp.x % 16);
		this->z = (int)(bp.z % 16);
	}
};

inline ChunkPos ChunkPos::ZERO = {0, 0};