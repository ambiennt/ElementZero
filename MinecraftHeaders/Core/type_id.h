#pragma once

#include "../dll.h"
#include <cstdint>

template <typename T>
class typeid_t {
public:
	uint16_t value;
	
	typeid_t(uint16_t value) : value(value) {}	
	typeid_t(const typeid_t &id) : value(id.value) {}
};