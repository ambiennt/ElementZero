#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

class ClientCacheBlobStatusPacket : public Packet {
public:
	std::vector<uint64_t> mMissingIds; // 0x28
	std::vector<uint64_t> mFoundIds; // 0x40

	inline ~ClientCacheBlobStatusPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(ClientCacheBlobStatusPacket, mFoundIds) == 0x40);