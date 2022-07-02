#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class EmotePacket : public Packet {
public:

    enum class Flags : uint8_t {
        NONE        = 0x0,
        SERVER_SIDE = 0x1,
    };

	ActorRuntimeID mRuntimeId; // 0x28
	std::string mPieceId; // 0x30 - https://github.com/JustTalDevelops/bedrock-emotes
    Flags mFlags; // 0x50 - actually a uint8_t in bds

	EmotePacket(ActorRuntimeID rid, std::string const& pieceId, EmotePacket::Flags flags = EmotePacket::Flags::NONE)
        : mRuntimeId(rid), mPieceId(pieceId), mFlags(flags) {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(EmotePacket) == 0x58);