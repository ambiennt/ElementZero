#pragma once

#include <hook.h>
#include "RakNetTypes.h"
#include "../dll.h"

class RakPeerHelper {
public:
	uint8_t pad[0x18]; // TODO
};

namespace RakNet {

enum class StartupResult : int32_t {
	RAKNET_STARTED = 0x0,
	RAKNET_ALREADY_STARTED = 0x1,
	INVALID_SOCKET_DESCRIPTORS = 0x2,
	INVALID_MAX_CONNECTIONS = 0x3,
	SOCKET_FAMILY_NOT_SUPPORTED = 0x4,
	SOCKET_PORT_ALREADY_IN_USE = 0x5,
	SOCKET_FAILED_TO_BIND = 0x6,
	SOCKET_FAILED_TEST_SEND = 0x7,
	PORT_CANNOT_BE_ZERO = 0x8,
	FAILED_TO_CREATE_NETWORK_THREAD = 0x9,
	COULD_NOT_GENERATE_GUID = 0xA,
	STARTUP_OTHER_FAILURE = 0xB,
};

class RakPeer /*: public RakPeerInterface, public RNS2EventHandler*/ {
public:
	MCAPI RakPeer();

	inline RakNet::SystemAddress GetSystemAddressFromGuid(RakNet::RakNetGUID guid) const {
		return CallServerClassMethod<RakNet::SystemAddress>(
			"?GetSystemAddressFromGuid@RakPeer@RakNet@@UEBA?AUSystemAddress@2@URakNetGUID@2@@Z", this, guid);
	}

	inline void SetOfflinePingResponse(const char *data, const uint32_t length) {
		CallServerClassMethod<void>("?SetOfflinePingResponse@RakPeer@RakNet@@UEAAXPEBDI@Z", this, data, length);
	}
};

} // namespace RakNet