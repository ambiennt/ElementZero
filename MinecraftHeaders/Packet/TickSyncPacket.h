#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class TickSyncPacket : public Packet {
public:
	int64_t mClientRequestTimestamp; // 0x28
	int64_t mServerReceptionTimestamp; // 0x30

	TickSyncPacket(int64_t clientReqTimestamp, int64_t serverReceiveTimestamp) :
		mClientRequestTimestamp(clientReqTimestamp), mServerReceptionTimestamp(serverReceiveTimestamp) {}
	inline ~TickSyncPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(TickSyncPacket, mServerReceptionTimestamp) == 0x30);