#pragma once

#include <string>

class SavedData {
public:
	bool mDirty;
	std::string mId;

	virtual ~SavedData();
	virtual void deserialize(class CompoundTag const &);
	virtual void serialize(class CompoundTag &) const;
};

static_assert(sizeof(SavedData) == 0x30);