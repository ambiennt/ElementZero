#pragma once

#include <functional>
#include "../Core/Packet.h"
#include "../dll.h"

struct ResourcePacksInfoData {
	bool mTexturePackRequired;
	bool mHasScripts;
	bool mHasExceptions;
	char pad[0x35];
};

static_assert(offsetof(ResourcePacksInfoData, mHasExceptions) == 0x2);
static_assert(sizeof(ResourcePacksInfoData) == 0x38);

class ResourcePacksInfoPacket : public Packet {
public:
	ResourcePacksInfoData data;

	inline ~ResourcePacksInfoPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(ResourcePacksInfoPacket, data) == 0x28);
static_assert(sizeof(ResourcePacksInfoPacket) == 0x60);