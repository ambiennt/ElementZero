#pragma once

#include <functional>
#include "HashedString.h"

class StringKey : public HashedString {
public:
	using HashedString::HashedString;
	using HashedString::operator==;
	using HashedString::operator!=;

	const StringKey* mMatch;

	// this is weird to copy the hashedstring but whatever, its what vanilla does
	StringKey(const HashedString &str) : HashedString(str), mMatch(nullptr) {}
};

namespace std {

template <> struct hash<StringKey> {
	std::size_t operator()(StringKey const &s) const noexcept { return s.getHash(); }
};

} // namespace std