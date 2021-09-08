#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class SetActorMotionPacket : public Packet {
public:
    ActorRuntimeID rid; // 0x28
    Vec3 motion;        // 0x30

    inline ~SetActorMotionPacket() {}
    MCAPI virtual MinecraftPacketIds getId() const;
    MCAPI virtual std::string getName() const;
    MCAPI virtual void write(BinaryStream &) const;
    MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(SetActorMotionPacket, rid) == 40);
static_assert(offsetof(SetActorMotionPacket, motion) == 48);