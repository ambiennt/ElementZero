#pragma once

#include <vector>
#include <array>

#include "../FakeGSL/string_span.h"
#include "../dll.h"

class Facing {
public:
	enum class Name : int8_t {
		Down             = 0,
		Up               = 1,
		North            = 2,
		South            = 3,
		West             = 4,
		East             = 5,
		Max              = 6,
		Undefined        = 6,
		NumCullingIds    = 7
	};

	struct Plane {
		MCAPI static class std::vector<uint8_t> HORIZONTAL;
	};

	MCAPI static int32_t const *const STEP_X;
	MCAPI static int32_t const *const STEP_Y;
	MCAPI static int32_t const *const STEP_Z;
	MCAPI static class Vec3 const *const NORMAL;
	MCAPI static uint8_t const *const OPPOSITE_FACING;
	MCAPI static enum Name const *const BY2DDATA;
	MCAPI static enum Name const *const DIRECTIONS;
	MCAPI static class BlockPos const *const DIRECTION;
	MCAPI static class std::vector<uint8_t> const ALL_FACES;
	MCAPI static class std::array<class std::vector<uint8_t>, 6> const ALL_EXCEPT;
	MCAPI static class std::array<class std::vector<uint8_t>, 6> const ALL_EXCEPT_AXIS_Y;

	MCAPI static int32_t getStepX(uint8_t);
	MCAPI static int32_t getStepY(uint8_t);
	MCAPI static int32_t getStepZ(uint8_t);
	MCAPI static uint8_t getOpposite(uint8_t);
	MCAPI static uint8_t fromVec3(class Vec3 const &);
	MCAPI static gsl::cstring_span<> toString(uint8_t);
};