#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"
#include "../Actor/Player.h"
#include "../dll.h"

#include <bitset>

class PlayerAuthInputPacket : public Packet {
public:
    Vec2 mRot;
    Vec3 mPos;
    float mRotYHead;
    Vec2 mMotion;
    Vec3 mGazeDirection; // for VR mode
    std::bitset<25> mInputData;
    InputMode mInputMode;
    ClientPlayMode mPlayMode;

    inline ~PlayerAuthInputPacket() {}
    MCAPI virtual MinecraftPacketIds getId() const;
    MCAPI virtual std::string getName() const;
    MCAPI virtual void write(BinaryStream &) const;
    MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};