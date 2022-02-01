#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class ShowProfilePacket : public Packet {
public:
	std::string mPlayerXUID; // 0x28

	inline ~ShowProfilePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};