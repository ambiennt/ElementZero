#pragma once

#include "../dll.h"

#include "Automation.h"

class IMinecraftApp {
public:
	virtual ~IMinecraftApp();
	virtual class Minecraft* getPrimaryMinecraft(void);
	virtual class Automation::AutomationClient getAutomationClient(void);
	virtual bool isEduMode(void);
	virtual bool isDedicatedServer(void);
	virtual void onNetworkMaxPlayersChanged(uint32_t newMaxPlayerCount);
	virtual class IGameModuleShared* getGameModule(void);
};