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

enum class Compressibility : unsigned int {
  Compressible    = 0,
  Incompressible  = 1
};

enum class MinecraftPacketIds;
enum class StreamReadResult;
enum class ExtendedStreamReadResult;
enum class MinecraftPacketIds;
class BinaryStream;
class ReadOnlyBinaryStream;

class Packet {
public:
  PacketPriority priority     = PacketPriority::MEDIUM_PRIORITY;
  int reliability             = 1; // NetworkPeer::Reliability
  unsigned char clientSubId   = 0;
  int64_t handler             = 0;
  unsigned int compress_type  = 0; // Compressibility::Compressible

  inline Packet(unsigned int compress) : compress_type(!compress) {}
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
static_assert(offsetof(Packet, compress_type) == 0x20);
static_assert(sizeof(Packet) == 0x28);