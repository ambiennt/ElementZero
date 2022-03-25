#pragma once

#include <cstdint>

class ActorRuntimeID {
public:
	uint64_t value = 0;

	inline ActorRuntimeID() {}
	inline ActorRuntimeID(uint64_t value) : value(value) {}

	ActorRuntimeID& operator=(ActorRuntimeID const &rhs) {
		this->value = rhs.value;
		return *this;
	}
	bool operator==(ActorRuntimeID const &rhs) const { return (this->value == rhs.value); }
	bool operator!=(ActorRuntimeID const &rhs) const { return (this->value != rhs.value); }
};