#pragma once

#include "../Math/Vec3.h"

class CommandPosition {
public:
	Vec3 mOffset;
	bool mRelativeX, mRelativeY, mRelativeZ, mLocal;
};

class CommandPositionFloat : public CommandPosition {
public:
};