#pragma once

#include "mce.h"

class ContentIdentity {
public:
	mce::UUID mUUID; // 0x0
	bool mValid; // 0x10
};

static_assert(sizeof(ContentIdentity) == 0x18);