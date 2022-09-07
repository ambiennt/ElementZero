#pragma once

#include "../Core/Packet.h"
#include "../Core/ConnectionRequest.h"
#include "../dll.h"

class SubClientLoginPacket : public Packet {
public:
	std::unique_ptr<SubClientConnectionRequest> mConnectionRequest;

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
	MCAPI virtual bool disallowBatching() const;
};

static_assert(offsetof(SubClientLoginPacket, mConnectionRequest) == 0x28);
static_assert(sizeof(SubClientLoginPacket) == 0x30);