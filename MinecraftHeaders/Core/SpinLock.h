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
	inline ~SpinLock();
	MCAPI uint64_t _getThreadId() const;
	MCAPI void lock() const;
	MCAPI void unlock() const;;
};