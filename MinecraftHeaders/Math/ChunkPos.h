#pragma once

#include "Vec3.h"
#include "BlockPos.h"
#include "../dll.h"

class ChunkPos {
public:
	int32_t x = 0, z = 0;

	static const ChunkPos ZERO;

	ChunkPos() {}
	inline ~ChunkPos() {}
	ChunkPos(int32_t x, int32_t z) : x(x), z(z) {}
	ChunkPos(ChunkPos const& rhs) : x(rhs.x), z(rhs.z) {}
	ChunkPos(BlockPos const& bp) : x((int32_t)(bp.x >> 4)), z((int32_t)(bp.z >> 4)) {}

	ChunkPos(Vec3 const& vec) {
		BlockPos bp(vec);
		this->x = bp.x >> 4;
		this->z = bp.z >> 4;
	}
};

inline const ChunkPos ChunkPos::ZERO = {0, 0};