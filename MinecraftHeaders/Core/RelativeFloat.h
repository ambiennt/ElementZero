#pragma once

#include "../dll.h"

class RelativeFloat {
public:
	float value;
	bool is_relative;

	RelativeFloat(float value) : value(value), is_relative(true) {}

	inline float getFloat(float center) const {
		if (this->is_relative) {
			return center + this->value;
		}
		return this->value;
	}
};