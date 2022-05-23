#pragma once

#include "../dll.h"
#include "Core.h"

class Random {
public:
	Core::Random mRandom; // 0x0

	MCAPI int32_t nextInt(int32_t min, int32_t max);
	MCAPI float nextFloat();
	MCAPI float nextGaussianFloat();
	MCAPI int32_t nextGaussianInt(int32_t n);
};