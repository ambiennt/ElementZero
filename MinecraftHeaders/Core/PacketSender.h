#pragma once

#include <vector>
#include <functional>

class Packet;
class NetworkIdentifier;
class NetworkIdentifierWithSubId;

class PacketSender {
public:
	uint8_t mSenderSubId;

	virtual ~PacketSender() {}
	virtual void send(Packet &)                                                                 = 0;
	virtual void sendToServer(Packet &)                                                         = 0;
	virtual void sendToClient(NetworkIdentifier const &, Packet const &, uint8_t subId)         = 0;
	virtual void sendToClients(std::vector<NetworkIdentifierWithSubId> const &, Packet const &) = 0;
	virtual void sendBroadcast(Packet const &)                                                  = 0;
	virtual void sendBroadcast(NetworkIdentifier const &, uint8_t mSubId, Packet const &)       = 0;
	virtual void flush(NetworkIdentifier const &, std::function<void()>)                        = 0;
};