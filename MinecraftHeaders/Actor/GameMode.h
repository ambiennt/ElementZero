#pragma once

#include "Player.h"
#include "../dll.h"

class GameMode {
public:
	Player* mPlayer;
	// TODO: add fields
	
	MCAPI virtual ~GameMode();
};