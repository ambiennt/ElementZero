#pragma once

#include "../dll.h"
#include "../Actor/MobEffect.h"
#include <modutils.h>

class Potion {
public:

	BUILD_ACCESS_MUT(int32_t, mId, 0x0);
	BUILD_ACCESS_MUT(std::string, mNameId, 0x8);
	BUILD_ACCESS_MUT(std::string, mPrefix, 0x28);
	BUILD_ACCESS_MUT(std::vector<class MobEffectInstance>, mEffects, 0x48);
	BUILD_ACCESS_MUT(std::vector<std::string>, mDescriptionIds, 0x60);

	using uint8Arr4 = uint8_t[4];
	BUILD_ACCESS_MUT(uint8Arr4, mVar, 0x78);

	MCAPI static int32_t mLastId;

	inline static int32_t getLastId() { return mLastId; }
};