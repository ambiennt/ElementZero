#pragma once

#include "../Core/Packet.h"
#include "../Command/CommandOriginData.h"
#include "../dll.h"

class CommandRequestPacket : public Packet {
public:
	std::string mCommand; // 0x28
	CommandOriginData mOrigin; // 0x48
	bool mIsInternalSource = false; // 0x88 - if the command is run from within the server?

	CommandRequestPacket(std::string cmd, CommandOriginData origin, bool isInternal) : mCommand(cmd), mOrigin(origin), mIsInternalSource(isInternal) {}
	inline ~CommandRequestPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(CommandRequestPacket, mCommand) == 0x28);
static_assert(offsetof(CommandRequestPacket, mOrigin) == 0x48);
static_assert(offsetof(CommandRequestPacket, mIsInternalSource) == 0x88);
static_assert(sizeof(CommandRequestPacket) == 0x90);