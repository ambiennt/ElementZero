#pragma once

#include "../dll.h"

template <typename Type, typename Store>
class AutomaticID {
public:
	Store value{};

	// make it non-POD
	inline ~AutomaticID() noexcept = default;
	inline AutomaticID() = default;
	inline AutomaticID(Store value) : value(value) {}
	inline constexpr operator Store() const noexcept { return this->value; }
};