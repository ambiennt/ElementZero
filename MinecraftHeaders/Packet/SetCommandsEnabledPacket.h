#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class SetCommandsEnabledPacket : public Packet {
public:

	bool mCommandsEnabled; // 0x28

	SetCommandsEnabledPacket(bool enabled) : mCommandsEnabled(enabled) {}
	inline ~SetCommandsEnabledPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};