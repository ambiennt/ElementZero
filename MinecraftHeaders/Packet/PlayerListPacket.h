#pragma once

#include <vector>

#include "../Core/Packet.h"
#include "../Core/mce.h"
#include "../Actor/ActorUniqueID.h"
#include "../Actor/Skin/SerializedSkin.h"
#include "../dll.h"

class PlayerListPacket : public Packet {
public:
  std::vector<class PlayerListEntry> entries;
  enum PlayerListPacketType type;

  inline ~PlayerListPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

class PlayerListEntry {
public:
  ActorUniqueID uid;
  mce::UUID uuid;
  std::string name, xuid, platform_online_id;

  enum struct BuildPlatform : int {
    Unknown          = -1,
    Google           = 1,
    iOS              = 2,
    OSX              = 3,
    Amazon           = 4,
    GearVR           = 5,
    UWP              = 7,
    Win32            = 8,
    Dedicated        = 9,  // bds
    PS4              = 10, // orbis
    Nx               = 11,
    Xbox             = 12,
    WindowsPhone     = 13
  } platform;

  SerializedSkin skin;
  bool teacher, host;

  MCAPI ~PlayerListEntry();
  MCAPI void write(BinaryStream &) const;
  MCAPI StreamReadResult read(ReadOnlyBinaryStream &);
};

enum PlayerListPacketType {
  Add     = 0,
  Remove  = 1
};