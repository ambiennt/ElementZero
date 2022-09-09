#pragma once

#include "../dll.h"

#include "Bedrock.h"
#include "Minecraft.h"
#include "Automation.h"
#include "MinecraftApp.h"

#include <memory>
#include <atomic>

class ServerInstanceEventCoordinator;
class ConsoleInputReader;
class AppConfigs;
class IGameModuleShared;

class DedicatedServer : public IMinecraftApp, public Bedrock::AppIsland {
public:
	virtual ~DedicatedServer();

	enum class StartResult : int32_t {
		Success = 0x0,
		PortOccupied = 0x1,
		InvalidSettings = 0x2,
	};

	Minecraft *mMinecraft; // 0x18
	std::unique_ptr<Automation::AutomationClient> mAutomationClient; // 0x20
	std::unique_ptr<ServerInstanceEventCoordinator> mServerInstanceEventCoordinator; // 0x28
	std::atomic<bool> mWantsToQuit; // 0x30
	std::unique_ptr<ConsoleInputReader> mConsoleInputReader; // 0x38
	std::unique_ptr<AppConfigs> mAppConfig; // 0x40
	AppConfigs* mAppConfigServiceRegistrationToken; // 0x48 - ServiceRegistrationToken<AppConfigs>
	std::unique_ptr<IGameModuleShared> mGameModule; // 0x50

	inline void doAsyncStop() { this->mWantsToQuit = true; }
};

static_assert(offsetof(DedicatedServer, mMinecraft) == 0x18);
static_assert(sizeof(DedicatedServer) == 0x58);