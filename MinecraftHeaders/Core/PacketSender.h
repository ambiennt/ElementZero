#pragma once

#include <vector>
#include <functional>
#include "../Net/NetworkIdentifier.h"

class Packet;
class NetworkHandler;
class NetEventCallback;
class Player;

class PacketSender {
public:
	uint8_t mSenderSubId;

	virtual ~PacketSender();
	virtual void send(Packet &)                                                                 = 0;
	virtual void sendToServer(Packet &)                                                         = 0;
	virtual void sendToClient(NetworkIdentifier const &, Packet const &, uint8_t subId)         = 0;
	virtual void sendToClients(std::vector<NetworkIdentifierWithSubId> const &, Packet const &) = 0;
	virtual void sendBroadcast(Packet const &)                                                  = 0;
	virtual void sendBroadcast(NetworkIdentifier const &, uint8_t mSubId, Packet const &)       = 0;
	virtual void flush(NetworkIdentifier const &, std::function<void()> &&callback)             = 0;
};

class LoopbackPacketSender : public PacketSender {
public:
	NetworkHandler* mNetwork; // 0x10
	std::vector<NetEventCallback*> mLoopbackCallbacks; // 0x18
	const std::vector<std::unique_ptr<Player>>* mUserList; // 0x30
	std::vector<NetworkIdentifierWithSubId> mTempUserIds; // 0x38
};

static_assert(sizeof(LoopbackPacketSender) == 0x50);