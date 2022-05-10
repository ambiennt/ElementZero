#pragma once

#include "../Core/Packet.h"
#include "../Container/ContainerID.h"
#include "../Actor/ActorUniqueID.h"
#include "../Math/BlockPos.h"
#include "../Container/ContainerType.h"
#include "../dll.h"

class ContainerOpenPacket : public Packet {
public:
  ContainerID mContainerId = ContainerID::Invalid;
  ContainerType mType = ContainerType::CONTAINER;
  BlockPos mPos;
  ActorUniqueID mEntityUniqueID;

  inline ~ContainerOpenPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(ContainerOpenPacket, mContainerId) == 40);
static_assert(offsetof(ContainerOpenPacket, mType) == 41);
static_assert(offsetof(ContainerOpenPacket, mPos) == 44);
static_assert(offsetof(ContainerOpenPacket, mEntityUniqueID) == 56);