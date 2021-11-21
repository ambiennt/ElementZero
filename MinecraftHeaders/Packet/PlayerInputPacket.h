#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec2.h"
#include "../dll.h"

class PlayerInputPacket : public Packet {
public:
    Vec2 mMotion;
    bool mIsJumping = false, mIsSneaking = false;

    inline ~PlayerInputPacket() {}
    MCAPI virtual MinecraftPacketIds getId() const;
    MCAPI virtual std::string getName() const;
    MCAPI virtual void write(BinaryStream &) const;
    MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};