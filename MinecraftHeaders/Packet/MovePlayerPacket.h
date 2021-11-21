#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Actor/Player.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class MovePlayerPacket : public Packet {
public:
    ActorRuntimeID mRuntimeId;
    Vec3 mPos;
    Vec2 mRot;
    float mRotYHead;
    Player::PositionMode mPositionMode;
    bool mOnGround;
    ActorRuntimeID mRidingActorId;
    int mTeleportCause;
    int mSourceEntityType;

    inline ~MovePlayerPacket() {}
    MCAPI virtual MinecraftPacketIds getId() const;
    MCAPI virtual std::string getName() const;
    MCAPI virtual void write(BinaryStream &) const;
    MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(MovePlayerPacket, mRuntimeId) == 40);
static_assert(offsetof(MovePlayerPacket, mPos) == 48);
static_assert(offsetof(MovePlayerPacket, mRot) == 60);
static_assert(offsetof(MovePlayerPacket, mRotYHead) == 68);
static_assert(offsetof(MovePlayerPacket, mPositionMode) == 72);
static_assert(offsetof(MovePlayerPacket, mOnGround) == 73);
static_assert(offsetof(MovePlayerPacket, mRidingActorId) == 80);
static_assert(offsetof(MovePlayerPacket, mTeleportCause) == 88);
static_assert(offsetof(MovePlayerPacket, mSourceEntityType) == 92);