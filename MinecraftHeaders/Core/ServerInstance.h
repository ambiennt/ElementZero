#pragma once

#include "../Core/Core.h"
#include "../Core/mce.h"
#include "../RakNet/RakNetTypes.h"
#include <modutils.h>
#include "../dll.h"

#include <functional>
#include <atomic>
#include <chrono>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>

class ServerInstance {
public:

	enum class InstanceState : int32_t {
		Running = 0,
		Suspended = 1,
		WaitingLeaveGame = 2,
		Stopped = 3,
		NotStarted = 4,
	};

	CLASS_FIELD(mApp, 0x88, const class IMinecraftApp *);
	CLASS_FIELD(mMinecraft, 0x90, std::unique_ptr<class Minecraft>);
	CLASS_FIELD(mNetwork, 0x98, std::unique_ptr<class NetworkHandler>);
	CLASS_FIELD(mPacketSender, 0xA0, std::unique_ptr<class LoopbackPacketSender>);
	CLASS_FIELD(mSimTimer, 0xA8, std::unique_ptr<class Timer>);
	CLASS_FIELD(mRealTimer, 0xB0, std::unique_ptr<class Timer>);
	CLASS_FIELD(mScheduler, 0xB8, std::unique_ptr<class Scheduler>);
	CLASS_FIELD(mEducationOptions, 0xC0, std::unique_ptr<class EducationOptions>);
	CLASS_FIELD(mStorage, 0xC8, class LevelStorage*);
	CLASS_FIELD(mNetworkGUID, 0xD0, struct RakNet::RakNetGUID);
	CLASS_FIELD(mInUpdate, 0xE0, std::atomic<bool>);
	CLASS_FIELD(mWriteRefCounter, 0xE4, std::atomic<int32_t>);
	CLASS_FIELD(mThreadShouldJoin, 0xE8, std::atomic<bool>);
	CLASS_FIELD(mServerThreadActive, 0xE9, std::atomic<bool>);
	//CLASS_FIELD(mEventCoordinator, 0xF0, gsl::not_null<Bedrock::NonOwnerPointer<class ServerInstanceEventCoordinator>>);
	CLASS_FIELD(mInstanceState, 0xF8, std::atomic<enum ServerInstance::InstanceState>);
	//CLASS_FIELD(mCommandQueue, 0x100, class SPSCQueue<std::function<void (void)>, 512>);
	CLASS_FIELD(mServerInstanceThread, 0x150, std::thread);
	CLASS_FIELD(mResumeMutex, 0x160, std::mutex);
	CLASS_FIELD(mResumeSignal, 0x1B0, std::condition_variable);
	CLASS_FIELD(mScriptEngine, 0x1F8, std::unique_ptr<class MinecraftServerScriptEngine>);
	CLASS_FIELD(mLevelCorruptCallback, 0x200, std::function<void()>);
	CLASS_FIELD(mHandledLevelCorruption, 0x240, bool);
	CLASS_FIELD(mTextFilteringProcessor, 0x248, std::unique_ptr<class TextFilteringProcessor>);
	CLASS_FIELD(mWakeupInterval, 0x250, std::chrono::duration<int64_t, std::ratio<1, 1000000>>);
	CLASS_FIELD(mLevelId, 0x258, std::string);
	CLASS_FIELD(mWorldSessionEndPoint, 0x278, std::unique_ptr<class WorldSessionEndPoint>);
	//CLASS_FIELD(mStorageAreaForLevel, 0x280, std::shared_ptr<class Core::FileStorageArea>);
	CLASS_FIELD(mEnableItemStackNetManager, 0x290, bool); // server auth inventory
	//CLASS_FIELD(mLevelStorageFileEndPoint, 0x298, std::shared_ptr<class Bedrock::FileLogEndPoint>);
	CLASS_FIELD(mLevelStoragePerfLog, 0x2A8, std::unique_ptr<class LevelStoragePerfLog>);
	//CLASS_FIELD(mLevelStoragePerfLogServiceRegistrationToken, 0x2B0, class ServiceRegistrationToken<class LevelStoragePerfLog>);
	CLASS_FIELD(mbInitialized, 0x2B8, bool);
	CLASS_FIELD(mbFlaggedForEarlyDestruction, 0x2B9, bool);
	//CLASS_FIELD(mServiceRegistrationToken, 0x2C0, class ServiceRegistrationToken<class ServerInstance>);

	MCAPI void queueForServerThread(std::function<void()>);
};