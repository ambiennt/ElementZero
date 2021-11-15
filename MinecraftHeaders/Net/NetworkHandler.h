#pragma once

#include <memory>
#include <chrono>
#include <bitset>
#include <queue>
#include <vector>

#include "NetworkPeer.h"
#include "NetworkIdentifier.h"

#include "../dll.h"

class PacketObserver;
class Scheduler;
class NetworkPacketRecoder;
class EncryptedNetworkPeer;
class BatchedNetworkPeer;

class NetworkHandler {
public:
  class Connection {
  public:
    NetworkIdentifier id;
    int type;
    std::weak_ptr<NetworkPacketRecoder> packet_recorder;
    std::weak_ptr<EncryptedNetworkPeer> encrypted;
    std::weak_ptr<BatchedNetworkPeer> batched;
    std::shared_ptr<NetworkPeer> shared;
    std::chrono::steady_clock::time_point time_a, time_b;
    bool should_close_connection, disconnected;
    std::bitset<2> channel_status;
    std::queue<std::string> packet_queue;
    std::array<std::vector<std::string>, 2> buffer_arr;

    MCAPI Connection(
        NetworkIdentifier const &id, std::shared_ptr<NetworkPeer> shared, std::chrono::steady_clock::time_point time,
        bool flag, PacketObserver *, Scheduler &);
    MCAPI ~Connection();
    MCAPI NetworkPeer::DataStatus receivePacket(std::string &);

    inline bool isChannelPaused(uint32_t chan_id) { return channel_status.test(chan_id); }
  };
  MCAPI void disconnect();
  MCAPI void runEvents();
  MCAPI class NetworkPeer *getPeerForUser(class NetworkIdentifier const &);
};

static_assert(offsetof(NetworkHandler::Connection, packet_recorder) == 160);