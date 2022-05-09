#pragma once

#include <cstdint>
#include "../dll.h"

struct ActorUniqueID {
	int64_t value = 0; // SIGNED INT64

	MCAPI static ActorUniqueID const INVALID_ID;

	inline ActorUniqueID() {}
	inline ActorUniqueID(int64_t value) : value(value) {}

	ActorUniqueID& operator=(ActorUniqueID const &rhs) {
		this->value = rhs.value;
		return *this;
	}
	inline bool operator==(ActorUniqueID const &rhs) const { return (this->value == rhs.value); }
	inline bool operator!=(ActorUniqueID const &rhs) const { return !(*this == rhs); }
};