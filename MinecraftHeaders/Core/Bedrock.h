#pragma once

#include "../dll.h"

#include <memory>

namespace Bedrock {

class ActivationArguments;
class SignalReceiver;

class IIslandCore {
public:
	virtual ~IIslandCore();
	virtual uint16_t getId();
	virtual bool start();
	virtual bool suspend();
	virtual bool resume();
	virtual bool stop();
	virtual void mainUpdate();
	virtual void processActivationArguments(const Bedrock::ActivationArguments *);
};

class AppIsland : public IIslandCore {
public:
	std::unique_ptr<class Bedrock::SignalReceiver> mSignalRcvr; // 0x8
};

}

static_assert(offsetof(Bedrock::AppIsland, mSignalRcvr) == 0x8);