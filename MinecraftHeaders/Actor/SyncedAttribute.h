#pragma once

#include <string>

class SyncedAttribute {
public:
	std::string name;
	float min, current, max;
};

static_assert(sizeof(SyncedAttribute) == 0x30);