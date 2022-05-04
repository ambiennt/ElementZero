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

class ServerInstance {
public:

	enum class InstanceState : int32_t {
		Running = 0,
		Suspended = 1,
		WaitingLeaveGame = 2,
		Stopped = 3,
		NotStarted = 4,
	};

	BUILD_ACCESS_MUT(const class IMinecraftApp *, mApp, 0x88);
	BUILD_ACCESS_MUT(std::unique_ptr<class Minecraft>, mMinecraft, 0x90);
	BUILD_ACCESS_MUT(std::unique_ptr<class NetworkHandler>, mNetwork, 0x98);
	BUILD_ACCESS_MUT(std::unique_ptr<class LoopbackPacketSender>, mPacketSender, 0xA0);
	BUILD_ACCESS_MUT(std::unique_ptr<class Timer>, mSimTimer, 0xA8);
	BUILD_ACCESS_MUT(std::unique_ptr<class Timer>, mRealTimer, 0xB0);
	BUILD_ACCESS_MUT(std::unique_ptr<class Scheduler>, mScheduler, 0xB8);
	BUILD_ACCESS_MUT(std::unique_ptr<class EducationOptions>, mEducationOptions, 0xC0);
	BUILD_ACCESS_MUT(class LevelStorage*, mStorage, 0xC8);
	BUILD_ACCESS_MUT(struct RakNet::RakNetGUID, mNetworkGUID, 0xD0);
	BUILD_ACCESS_MUT(std::atomic<bool>, mInUpdate, 0xE0);
	BUILD_ACCESS_MUT(std::atomic<int32_t>, mWriteRefCounter, 0xE4);
	BUILD_ACCESS_MUT(std::atomic<bool>, mThreadShouldJoin, 0xE8);
	BUILD_ACCESS_MUT(std::atomic<bool>, mServerThreadActive, 0xE9);
	//BUILD_ACCESS_MUT(gsl::not_null<Bedrock::NonOwnerPointer<class ServerInstanceEventCoordinator>>, mEventCoordinator, 0xF0);
	BUILD_ACCESS_MUT(std::atomic<enum ServerInstance::InstanceState>, mInstanceState, 0xF8);
	//BUILD_ACCESS_MUT(class SPSCQueue<std::function<void (void)>, 512>, mCommandQueue, 0x100);
	BUILD_ACCESS_MUT(std::thread, mServerInstanceThread, 0x150);
	BUILD_ACCESS_MUT(std::mutex, mResumeMutex, 0x160);
	BUILD_ACCESS_MUT(std::condition_variable, mResumeSignal, 0x1B0);
	BUILD_ACCESS_MUT(std::unique_ptr<class MinecraftServerScriptEngine>, mScriptEngine, 0x1F8);
	BUILD_ACCESS_MUT(std::function<void()>, mLevelCorruptCallback, 0x200);
	BUILD_ACCESS_MUT(bool, mHandledLevelCorruption, 0x240);
	BUILD_ACCESS_MUT(std::unique_ptr<class TextFilteringProcessor>, mTextFilteringProcessor, 0x248);
	//BUILD_ACCESS_MUT(std::chrono::duration<int64_t, std::ratio<1, 1000000>>, mWakeupInterval, 0x250);
	BUILD_ACCESS_MUT(std::string, mLevelId, 0x258);
	BUILD_ACCESS_MUT(std::unique_ptr<class WorldSessionEndPoint>, mWorldSessionEndPoint, 0x278);
	//BUILD_ACCESS_MUT(std::shared_ptr<class Core::FileStorageArea>, mStorageAreaForLevel, 0x280);
	BUILD_ACCESS_MUT(bool, mEnableItemStackNetManager, 0x290); // server auth inventory
	//BUILD_ACCESS_MUT(std::shared_ptr<class Bedrock::FileLogEndPoint>, mLevelStorageFileEndPoint, 0x298);
	BUILD_ACCESS_MUT(std::unique_ptr<class LevelStoragePerfLog>, mLevelStoragePerfLog, 0x2A8);
	//BUILD_ACCESS_MUT(class ServiceRegistrationToken<class LevelStoragePerfLog>, mLevelStoragePerfLogServiceRegistrationToken, 0x2B0);
	BUILD_ACCESS_MUT(bool, mbInitialized, 0x2B8);
	BUILD_ACCESS_MUT(bool, mbFlaggedForEarlyDestruction, 0x2B9);
	//BUILD_ACCESS_MUT(class ServiceRegistrationToken<class ServerInstance>, mServiceRegistrationToken, 0x2C0);

	MCAPI void queueForServerThread(std::function<void()>);
};