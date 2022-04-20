#pragma once

#include <hook.h>

#include "../Core/Packet.h"
#include "../dll.h"

class TransferPacket : public Packet {
	std::string mServerAddress;
	int32_t mServerPort = 0;

public:
	inline ~TransferPacket() {}
	TransferPacket(std::string address, int32_t port) : mServerAddress(address), mServerPort(port) {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};