#pragma once

#include "../Core/Packet.h"
#include "../Command/CommandOriginData.h"
#include "../dll.h"

class CommandRequestPacket : public Packet {
public:
	std::string command;
	CommandOriginData data;
	bool internalSource = false;

	inline ~CommandRequestPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(CommandRequestPacket, command) == 0x28);
static_assert(offsetof(CommandRequestPacket, data) == 0x48);
static_assert(offsetof(CommandRequestPacket, internalSource) == 0x88);
static_assert(sizeof(CommandRequestPacket) == 0x90);