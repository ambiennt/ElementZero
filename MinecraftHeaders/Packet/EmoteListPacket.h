#pragma once

#include "../Core/Packet.h"
#include "../Core/mce.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"
#include <vector>

class EmoteListPacket : public Packet {
public:
    ActorRuntimeID mRuntimeId; // 0x28
    std::vector<mce::UUID> mEmotePieceIds; // 0x30

    static const int32_t MAX_EMOTE_PIECE_IDS; // max amount of emotes that the client can equip at once (amount of slots in the emote wheel, so 6)

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(EmoteListPacket) == 0x48);