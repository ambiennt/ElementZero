#pragma once

#include "Vec3.h"
#include "BlockPos.h"
#include "../dll.h"

class ChunkPos {
public:
	int32_t x = 0, z = 0;

	static ChunkPos ZERO;

	ChunkPos();
	ChunkPos(int32_t x, int32_t z) : x(x), z(z) {}
	inline ~ChunkPos() {}
	inline ChunkPos(BlockPos const& bp) {
		this->x = bp.x >> 4;
		this->z = bp.z >> 4;
	}
	inline ChunkPos(Vec3 const& vec) {
		BlockPos bp;
		bp.getBlockPos(vec);
		this->x = bp.x >> 4;
		this->z = bp.z >> 4;
	}
};

inline ChunkPos ChunkPos::ZERO = {0, 0};