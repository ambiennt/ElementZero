#pragma once

#include "../dll.h"

template <typename T> class typeid_t {
public:
	uint16_t value;
	
	typeid_t(uint16_t value) : value(value) {}	
	typeid_t(typeid_t const &id) : value(id.value) {}
};