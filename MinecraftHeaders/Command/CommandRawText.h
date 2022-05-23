#pragma once

#include <string>
#include "../dll.h"

class CommandRawText {
	std::string mText; // 0x0

public:
	inline std::string const &getText() const { return this->mText; }
};