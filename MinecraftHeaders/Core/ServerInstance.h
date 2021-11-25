#pragma once

#include <functional>
#include <modutils.h>
#include "../dll.h"

class ServerInstance {
public:

	BUILD_ACCESS_MUT(std::string, mLevelId, 0x258);
	BUILD_ACCESS_MUT(bool, mEnableItemStackNetManager, 0x290); // server auth inventory
	BUILD_ACCESS_MUT(bool, mbInitialized, 0x2B8);
	BUILD_ACCESS_MUT(bool, mbFlaggedForEarlyDistruction, 0x2B9);

	MCAPI void queueForServerThread(std::function<void()>);
};