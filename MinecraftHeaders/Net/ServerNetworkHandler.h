#pragma once

#include <hook.h>
#include "../Actor/ServerPlayer.h"
#include "NetworkIdentifier.h"
#include "../dll.h"

class Player;

class ServerNetworkHandler {
public:
  MCAPI void disconnectClient(NetworkIdentifier const &, unsigned char subid, std::string const &reason, bool hide);
  MCAPI void updateServerAnnouncement();

  void forceDisconnectClient(Player *player, bool hide) {
    CallServerClassMethod<void>("?_onPlayerLeft@ServerNetworkHandler@@AEAAXPEAVServerPlayer@@_N@Z", this, player, hide);
  }

  inline ServerPlayer* getServerPlayer(NetworkIdentifier const & netId) {
      return _getServerPlayer(netId, 0);
  }
  
  BASEAPI std::string &GetMotd();

  private:
      MCAPI ServerPlayer* _getServerPlayer(NetworkIdentifier const&, unsigned char);
};