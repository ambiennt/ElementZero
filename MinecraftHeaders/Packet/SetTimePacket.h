#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class SetTimePacket : public Packet {
public:
	int32_t mTime; // 0x28

	SetTimePacket(int32_t time) : mTime(time) {}
	inline ~SetTimePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};