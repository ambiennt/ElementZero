#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class ModalFormResponsePacket : public Packet {
public:
	unsigned int id;
	std::string content;

	inline ~ModalFormResponsePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};