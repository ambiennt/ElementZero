#pragma once

#include "../dll.h"
#include <modutils.h>

#include <atomic>

class SpinLock {
public:
	int64_t mNoThreadId; // 0x8
	std::atomic<uint64_t> mOwnerThread; // 0x10
	uint32_t mOwnerRefCount; // 0x18

	MCAPI SpinLock();
	//MCAPI ~SpinLock(void) const;
	MCAPI uint64_t _getThreadId(void) const;
	MCAPI void lock(void) const;
	MCAPI void unlock(void) const;
	//MCAPI bool try_lock(void) const;
	//MCAPI bool try_lock(uint64_t) const;
};