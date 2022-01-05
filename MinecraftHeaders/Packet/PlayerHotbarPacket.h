#pragma once

#include "../Core/Packet.h"
#include "../Core/ContainerID.h"
#include "../dll.h"

class PlayerHotbarPacket : public Packet {
public:
	uint32_t mSlot           = 0; // 0x28
	bool mShouldSelectSlot   = false; // 0x2C - whether or not the client is forced to select the mSlot when receiving this packet
	ContainerID mContainerId = ContainerID::Inventory; // 0x2D

	PlayerHotbarPacket(uint32_t slot, bool select, enum ContainerID id) : mSlot(slot), mShouldSelectSlot(select), mContainerId(id) {}
	inline ~PlayerHotbarPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(PlayerHotbarPacket, mSlot) == 0x28);
static_assert(offsetof(PlayerHotbarPacket, mShouldSelectSlot) == 0x2C);
static_assert(offsetof(PlayerHotbarPacket, mContainerId) == 0x2D);