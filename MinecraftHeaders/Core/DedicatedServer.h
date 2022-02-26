#pragma once

#include "../dll.h"

#include "Bedrock.h"
#include "Minecraft.h"
#include "Automation.h"

#include <memory>
#include <atomic>

class DedicatedServer : public IMinecraftApp, public Bedrock::AppIsland {
public:
	virtual ~DedicatedServer();

	Minecraft *mMinecraft; // 0x18
	std::unique_ptr<class Automation::AutomationClient> mAutomationClient; // 0x20
	std::unique_ptr<class ServerInstanceEventCoordinator> mServerInstanceEventCoordinator; // 0x28
	std::atomic<bool> mWantsToQuit; // 0x30
	std::unique_ptr<class ConsoleInputReader> mConsoleInputReader; // 0x38
	std::unique_ptr<class AppConfigs> mAppConfig; // 0x40
	class AppConfigs* mAppConfigServiceRegistrationToken; // 0x48 - ServiceRegistrationToken<AppConfigs>
	std::unique_ptr<class IGameModuleShared> mGameModule; // 0x50
};

static_assert(offsetof(DedicatedServer, mMinecraft) == 0x18);
static_assert(sizeof(DedicatedServer) == 0x58);