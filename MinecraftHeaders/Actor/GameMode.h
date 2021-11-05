#pragma once

#include "Player.h"
#include "../dll.h"

class GameMode {
public:
  Player* mPlayer;

  MCAPI virtual ~GameMode();
};