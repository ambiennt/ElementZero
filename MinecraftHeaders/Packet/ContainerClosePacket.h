#pragma once

#include "../Core/Packet.h"
#include "../Core/ContainerID.h"
#include "../dll.h"

class ContainerClosePacket : public Packet {
public:
	ContainerID mContainerId = ContainerID::Invalid;

	inline ~ContainerClosePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(ContainerClosePacket, mContainerId) == 40);