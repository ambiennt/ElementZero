#pragma once

#include "LevelData.h"
#include "../dll.h"

class LevelDataWrapper {
public:
	LevelData *rdata;
	LevelData data;

	LevelData &operator*() { return rdata ? *rdata : data; }
	LevelData const &operator*() const { return rdata ? *rdata : data; }
	LevelData *operator->() { return rdata ? rdata : &data; }
	LevelData const *operator->() const { return rdata ? rdata : &data; }

	inline void resetLevelDataPointer() { rdata = nullptr; }
	inline void setLevelData(LevelData &data) { rdata = &data; }
};