#pragma once

#include <cstdint>
#include <string>
#include <functional>

#include "../dll.h"

class NetworkPeer {
public:

  enum class Reliability : int {
    Reliable             = 0,
    ReliableOrdered      = 1,
    Unreliable           = 2,
    UnreliableSequenced  = 3
  };

  enum class DataStatus : int {
    HasData     = 0,
    NoData      = 1,
    BrokenData  = 2
  };

  struct NetworkStatus {
    int level;
    int ping, avgping;
    double packetloss, avgpacketloss;
  };

  virtual ~NetworkPeer();
  virtual void sendPacket(std::string, NetworkPeer::Reliability, int) = 0;
  virtual DataStatus receivePacket(std::string &)                     = 0;
  virtual NetworkStatus getNetworkStatus()                            = 0;
  MCAPI virtual void update();
  MCAPI virtual void flush(std::function<void(void)> &&);
};