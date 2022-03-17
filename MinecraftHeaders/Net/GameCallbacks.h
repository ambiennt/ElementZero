#pragma once

#include "../dll.h"

// no fields
// i cant find any symbols for this in BDS
// reference: ServerNetworkHandler::handle(NetworkIdentifier const &, PlayerHotbarPacket const &)
class GameCallbacks {
public:

	virtual ~GameCallbacks();
	virtual void onLevelCorrupt(void);
	virtual void onGameModeChanged(void);
	virtual void onTick(int32_t, int32_t);
	virtual void onInternetUpdate(void);
	virtual void onGameSessionReset(void);
	virtual void onLevelExit(void);
	virtual void updateScreens(void);
};