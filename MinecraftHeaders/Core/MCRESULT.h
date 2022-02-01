#pragma once

#include "../dll.h"

enum class MCCATEGORY : int8_t {
	Minecraft = 0,
	AutomationProtocol = 1,
	MinecraftCommand = 2
};

struct MCRESULT {
	bool mSuccess; // 0x0
	MCCATEGORY mCategory; // 0x1
	int16_t mCode; // 0x2

	constexpr bool operator==(MCRESULT const &rhs) const {
		return ((mSuccess == rhs.mSuccess) && (mCategory == rhs.mCategory) && (mCode == rhs.mCode));
	}
	constexpr bool operator!=(MCRESULT const &rhs) const {
		return ((mSuccess != rhs.mSuccess) || (mCategory != rhs.mCategory) || (mCode != rhs.mCode));
	}
};

MCAPI MCRESULT const MCRESULT_Success;