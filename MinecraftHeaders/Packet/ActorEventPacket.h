#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../Actor/ActorEvent.h"
#include "../dll.h"

class ActorEventPacket : public Packet {
public:
	ActorRuntimeID mRuntimeId; // 0x28
	ActorEvent mEventId; // 0x30
	int32_t mData; // 0x34 - depends on event id

	ActorEventPacket(ActorRuntimeID rid, ActorEvent event, int32_t data) : mRuntimeId(rid), mEventId(event), mData(data) {}
	inline ~ActorEventPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(ActorEventPacket, mEventId) == 0x30);
static_assert(offsetof(ActorEventPacket, mData) == 0x34);