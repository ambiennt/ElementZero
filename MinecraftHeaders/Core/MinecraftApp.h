#pragma once

#include "../dll.h"
#include "Automation.h"

class Minecraft;
class IGameModuleShared;

class IMinecraftApp {
public:
	virtual ~IMinecraftApp();
	virtual Minecraft* getPrimaryMinecraft();
	virtual Automation::AutomationClient getAutomationClient();
	virtual bool isEduMode();
	virtual bool isDedicatedServer();
	virtual void onNetworkMaxPlayersChanged(uint32_t newMaxPlayerCount);
	virtual IGameModuleShared* getGameModule();
};