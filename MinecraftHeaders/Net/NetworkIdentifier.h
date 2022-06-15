#pragma once

#include <boost/functional/hash.hpp>
#include "../RakNet/RakNetTypes.h"
#include <modutils.h>
#include "../dll.h"

class NetworkIdentifier {
public:

	enum class Type {
		RakNet   = 0,
		IPv4     = 1,
		IPv6     = 2,
		Generic  = 3
	};

	RakNet::RakNetGUID mGuid; // 0x0
	uint8_t pad[0x80]; // 0x10
	NetworkIdentifier::Type mType; // 0x90

	MCAPI bool operator==(NetworkIdentifier const &) const;
	MCAPI uint64_t getHash() const;
	MCAPI std::string getAddress() const;

	BASEAPI RakNet::SystemAddress getRealAddress() const;
};
static_assert(offsetof(NetworkIdentifier, mType) == 0x90);
static_assert(sizeof(NetworkIdentifier) == 0x98);

class NetworkIdentifierWithSubId {
public:
	NetworkIdentifier mId;
	uint8_t mSubId;
};
static_assert(sizeof(NetworkIdentifierWithSubId) == 0xA0);

namespace std {

template <> struct hash<NetworkIdentifier> {
	size_t operator()(const NetworkIdentifier &val) const { return val.getHash(); }
};

} // namespace std

namespace boost {

template <> struct hash<NetworkIdentifier> {
	size_t operator()(const NetworkIdentifier &val) const { return val.getHash(); }
};

} // namespace boost