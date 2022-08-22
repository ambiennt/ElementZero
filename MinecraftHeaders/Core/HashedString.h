#pragma once

#include <string>
#include <cstdint>

#include "../dll.h"

class HashedString {
	uint64_t mStrHash;
	std::string mStr;
public:
	constexpr inline static uint64_t VAL_64 = 0xCBF29CE484222325;
	constexpr inline static uint64_t PRIME_64 = 0x100000001B3;

	HashedString() : mStrHash(0) {}
	HashedString(const std::string& str) {
		this->mStr = str;
		this->mStrHash = this->computeHash(str);
	}
	HashedString(const char* str) : HashedString(std::string(str)) {}
	HashedString(const HashedString &rhs) : mStrHash(rhs.mStrHash), mStr(rhs.mStr) {}
	HashedString(HashedString &&rhs) : mStrHash(std::move(rhs.mStrHash)), mStr(std::move(rhs.mStr)) {}

	inline uint64_t getHash() const { return this->mStrHash; }
	inline const std::string &getString() const { return this->mStr; }
	constexpr inline uint64_t computeHash(const char *str) const {
		uint8_t currentChar = (uint8_t)(*str);
		if (!currentChar) return 0;
		uint64_t result = VAL_64;
		do {
			++str;
			result = currentChar ^ (PRIME_64 * result);
			currentChar = *str;
		} while (*str);
		return result;
	}
	constexpr uint64_t computeHash(const std::string& str) const {
		return this->computeHash(str.c_str());
	}

	inline bool operator==(HashedString const &rhs) const {
		return (this->mStrHash == rhs.mStrHash) && (this->mStr == rhs.mStr);
	}
	inline bool operator!=(HashedString const &rhs) const {
		return !(*this == rhs);
	}
};