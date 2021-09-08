#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class MovePlayerPacket : public Packet {
    public:
        ActorRuntimeID rid;                     // 0x28
        Vec3 pos;                               // 0x30
        float pitch = 0, yaw = 0, head_yaw = 0; // 0x3C, 0x40, 0x44
        uint8_t mode;                           // 0x48
        bool onGround;                          // 0x49
        ActorRuntimeID ridingActorId;           // 0x50
        int teleportCause;                      // 0x58

        inline ~MovePlayerPacket() {}
        MCAPI virtual MinecraftPacketIds getId() const;
        MCAPI virtual std::string getName() const;
        MCAPI virtual void write(BinaryStream &) const;
        MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(MovePlayerPacket, rid) == 40);
static_assert(offsetof(MovePlayerPacket, pos) == 48);
static_assert(offsetof(MovePlayerPacket, pitch) == 60);
static_assert(offsetof(MovePlayerPacket, yaw) == 64);
static_assert(offsetof(MovePlayerPacket, head_yaw) == 68);
static_assert(offsetof(MovePlayerPacket, mode) == 72);
static_assert(offsetof(MovePlayerPacket, onGround) == 73);
static_assert(offsetof(MovePlayerPacket, ridingActorId) == 80);
static_assert(offsetof(MovePlayerPacket, teleportCause) == 88);