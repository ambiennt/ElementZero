#pragma once

#include <cstdint>
#include "../dll.h"

class ActorRuntimeID {
public:
	uint64_t value = 0; // UNSIGNED INT64

	inline ActorRuntimeID() {}
	inline ActorRuntimeID(uint64_t value) : value(value) {}

	ActorRuntimeID& operator=(ActorRuntimeID const &rhs) {
		this->value = rhs.value;
		return *this;
	}
	inline bool operator==(ActorRuntimeID const &rhs) const { return (this->value == rhs.value); }
	inline bool operator!=(ActorRuntimeID const &rhs) const { return !(*this == rhs); }
};