#pragma once

#include <string>
#include <WinSock2.h>
#include "../Core/mce.h"
#include "../dll.h"

namespace RakNet {

struct SystemAddress {
private:
	MCAPI void ToString_New(bool writePort, char *dest, char portDelineator) const;
public:
	MCAPI SystemAddress();

	uint8_t pad1[0x80];
	uint16_t debugPort, systemIndex;
	uint8_t pad2[0x4];

	MCAPI SystemAddress &operator=(SystemAddress const &);
	MCAPI bool operator==(SystemAddress const &) const;

	inline std::string ToString(bool withPort = true) {
		char buffer[256];
		this->ToString_New(withPort, buffer, '|');
		return {buffer};
	}
};
static_assert(sizeof(RakNet::SystemAddress) == 0x88);

struct RakNetGUID;
MCAPI extern RakNetGUID const UNASSIGNED_RAKNET_GUID;

struct RakNetGUID {
	uint64_t g;
	uint16_t systemIndex;

	RakNetGUID() : g(-1), systemIndex(-1) {}
	RakNetGUID(uint64_t g, uint16_t systemIndex) : g(g), systemIndex(systemIndex) {}
};
static_assert(sizeof(RakNetGUID) == 0x10);

struct Packet {
	SystemAddress systemAddress;
	RakNetGUID guid;
	uint32_t length, bitSize;
	uint8_t *data;
	bool deleteData, wasGeneratedLocally;
};

} // namespace RakNet