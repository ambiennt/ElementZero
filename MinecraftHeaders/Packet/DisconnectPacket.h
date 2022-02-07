#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class DisconnectPacket : public Packet {
public:

	bool mSkipMessage; // 0x28
	std::string mMessage; // 0x30

	DisconnectPacket(bool skipMsg, std::string msg) : mSkipMessage(skipMsg), mMessage(msg) {}
	inline ~DisconnectPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(DisconnectPacket, mMessage) == 0x30);
static_assert(sizeof(DisconnectPacket) == 0x50);