#pragma once

#include <string>
#include "../dll.h"

namespace Core {

class Random {
public:

	uint32_t mSeed; // 0x0
	uint32_t _mt[624]; // 0x4
	int32_t _mti; // 0x9C4
	bool mHaveNextNextGaussian; // 0x9C8
	float mNextGuassian; // 0x9CC
	int32_t mInitedIdx; // 0x9D0

	MCAPI uint32_t _genRandInt32(void);
	MCAPI double nextGaussian(void);
	MCAPI void _setSeed(uint32_t seed);
};
static_assert(sizeof(Core::Random) == 0x9D4);

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

class FilePathManager {
public:
	bool mIsDedicatedServer; // 0x0
	PathBuffer<std::string> mRoot; // 0x8
	PathBuffer<std::string> mPackagePath; // 0x28
	PathBuffer<std::string> mDataUrl; // 0x48
	PathBuffer<std::string> mExternalFilePath; // 0x68
	PathBuffer<std::string> mTemporaryFilePath; // 0x88
	PathBuffer<std::string> mCacheFilePath; // 0xA8
	PathBuffer<std::string> mSettingsPath; // 0xC8
};

} // namespace Core

static_assert(sizeof(Core::FilePathManager) == 0xE8);