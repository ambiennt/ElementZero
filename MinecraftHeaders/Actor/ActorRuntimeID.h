#pragma once

#include <cstdint>

class ActorRuntimeID {
public:
  uint64_t value = 0; //rawID

  inline ActorRuntimeID() {}
  inline ActorRuntimeID(uint64_t value) : value(value) {}
};