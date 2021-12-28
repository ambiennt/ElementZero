#pragma once

#include <string>
#include "../dll.h"

#include <modutils.h>

namespace Core {

class Random {
public:
	BUILD_ACCESS_MUT(uint32_t, mSeed, 0x0);

	using arr624 = uint32_t[624];
	BUILD_ACCESS_MUT(arr624, _mt, 0x4);

	BUILD_ACCESS_MUT(int32_t, _mti, 0x9C4);
	BUILD_ACCESS_MUT(bool, mHaveNextNextGaussian, 0x9C8);
	BUILD_ACCESS_MUT(float, mNextNextGaussian, 0x9CC);
	BUILD_ACCESS_MUT(int32_t, mInitedIdx, 0x9D0);

	MCAPI uint32_t _genRandInt32(void);
	MCAPI double nextGaussian(void);
	MCAPI void _setSeed(uint32_t seed);
	//MCAPI int32_t nextInt(int32_t n);
};

class PathPart {
public:
	std::string data;
};

class Path : public PathPart {
public:
};

template <typename T> class PathBuffer {
	T value;
	operator T &() noexcept { return value; }
	operator T const &() const noexcept { return value; }
};

} // namespace Core