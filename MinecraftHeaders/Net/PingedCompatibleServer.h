#pragma once

#include "../dll.h"
#include "../RakNet/RakNetTypes.h"

enum class GameType : int32_t;

class PingedCompatibleServer {
public:
    std::string mName;
    std::string mWorldName;
    GameType mGameType;
    int32_t mProtocol;
    std::string mVersion;
    int32_t mPlayers;
    int32_t mMaxPlayers;
    std::string mOriginalAddress;
    RakNet::SystemAddress mAddress;
    uint32_t mPingTime;
    float mPingLatency;
    RakNet::RakNetGUID mHostGuid;
};