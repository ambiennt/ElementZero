#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class SetHealthPacket : public Packet {
public:
	int32_t mHealth;

	SetHealthPacket(int32_t health) : mHealth(health) {}
	inline ~SetHealthPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};