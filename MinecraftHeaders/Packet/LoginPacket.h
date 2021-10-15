#pragma once

#include "../Core/Packet.h"
#include "../Core/ConnectionRequest.h"
#include "../dll.h"

class LoginPacket : public Packet {
public:
  int64_t client_network_version;
  std::unique_ptr<ConnectionRequest> connection_request;

  inline ~LoginPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(LoginPacket, client_network_version) == 0x28);
static_assert(offsetof(LoginPacket, connection_request) == 0x30);
static_assert(sizeof(LoginPacket) == 0x38);