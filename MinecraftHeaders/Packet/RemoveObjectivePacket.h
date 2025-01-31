#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class RemoveObjectivePacket : public Packet {
public:
	std::string objective_name;

	inline ~RemoveObjectivePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};