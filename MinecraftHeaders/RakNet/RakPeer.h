#pragma once

#include <hook.h>
#include "RakNetTypes.h"
#include "../dll.h"

class RakPeerHelper {
public:
	uint8_t pad[0x18]; // TODO
};

namespace RakNet {

class RakPeerInterface {
public:
	virtual ~RakPeerInterface();
	// TODO: rest of vtable
};

class RNS2EventHandler {
public:
	virtual ~RNS2EventHandler();
	// TODO: rest of vtable
};

class RakPeer : public RakPeerInterface, public RNS2EventHandler {
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