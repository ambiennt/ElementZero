#pragma once

#include "../Core/Packet.h"
#include "../Core/ConnectionRequest.h"
#include "../dll.h"

class LoginPacket : public Packet {
public:
  int32_t mClientNetworkVersion;
  std::unique_ptr<ConnectionRequest> mConnectionRequest;

  inline ~LoginPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(LoginPacket, mClientNetworkVersion) == 0x28);
static_assert(offsetof(LoginPacket, mConnectionRequest) == 0x30);
static_assert(sizeof(LoginPacket) == 0x38);