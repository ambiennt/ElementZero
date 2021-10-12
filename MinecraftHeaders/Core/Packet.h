#pragma once

#include <cstdint>
#include <string>

enum class PacketPriority : unsigned int {
  IMMEDIATE_PRIORITY    = 0,
  HIGH_PRIORITY         = 1,
  MEDIUM_PRIORITY       = 2,
  LOW_PRIORITY          = 3,
  NUMBER_OF_PRIORITIES  = 4
};

enum class PacketReliability {
  UNRELIABLE                         = 0,
  UNRELIABLE_SEQUENCED               = 1,
  RELIABLE                           = 2,
  RELIABLE_ORDERED                   = 3,
  RELIABLE_SEQUENCED                 = 4,
  UNRELIABLE_WITH_ACK_RECEIPT        = 5,
  RELIABLE_WITH_ACK_RECEIPT          = 6,
  RELIABLE_ORDERED_WITH_ACK_RECEIPT  = 7,
  NUMBER_OF_RELIABILITIES            = 8
};

enum class StreamReadResult {};
enum class ExtendedStreamReadResult {};
enum class MinecraftPacketIds {};
class BinaryStream;
class ReadOnlyBinaryStream;

class Packet {
public:
  unsigned priority              = 2; // PacketPriority::MEDIUM_PRIORITY
  PacketReliability reliability  = PacketReliability::RELIABLE_ORDERED;
  unsigned char clientSubId      = 0;
  uint64_t handler               = 0;
  unsigned incompressible        = 0;

  inline Packet(unsigned compress) : incompressible(!compress) {}
  inline Packet() {}
  inline virtual ~Packet() {}
  virtual MinecraftPacketIds getId() const              = 0;
  virtual std::string getName() const                   = 0;
  virtual void write(BinaryStream &) const              = 0;
  virtual StreamReadResult read(ReadOnlyBinaryStream &) = 0;
  inline virtual ExtendedStreamReadResult readExtended(ReadOnlyBinaryStream &stream) {
    return (ExtendedStreamReadResult) read(stream);
  }
  inline virtual bool disallowBatching() const { return false; }
};

static_assert(offsetof(Packet, priority) == 0x8);
static_assert(offsetof(Packet, reliability) == 0xC);
static_assert(offsetof(Packet, clientSubId) == 0x10);
static_assert(offsetof(Packet, handler) == 0x18);
static_assert(offsetof(Packet, incompressible) == 0x20);
static_assert(sizeof(Packet) == 0x28);
