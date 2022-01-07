#pragma once

#include "../dll.h"

namespace Social {

enum class GamePublishSetting {
	NoMultiPlay      = 0,
	InviteOnly       = 1,
	FriendsOnly      = 2,
	FriendsOfFriends = 3,
	Public           = 4
};

enum class MultiplayerServiceIdentifier {
	Invalid     = -1,
	XboxLive    = 0,
	Nintendo    = 1,
	AdHoc       = 2,
	Playstation = 3,
	EDU         = 4,
	Mock        = 5
};

enum class ConnectionType : int16_t {
	Undefined   = -1,
	Local       = 0,
	IPv4        = 1,
	IPv6        = 2,
	NAT         = 3,
	UPNP        = 4,
	UnknownIP   = 5
};

}