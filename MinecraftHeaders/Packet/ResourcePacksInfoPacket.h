#pragma once

#include "../Core/Packet.h"
#include "../ResourcePack/ResourcePacksInfoData.h"
#include "../dll.h"

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