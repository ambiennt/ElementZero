#pragma once

#include "SharedPtr.h"

template <typename T> class WeakPtr {
public:
	SharedCounter<T> *counter;

	inline WeakPtr() : counter(nullptr) {}
	inline WeakPtr(SharedPtr<T> const &ref) : counter(ref.counter) {
		if (this->counter) {
			this->counter->addWeakRef();
		}
	}
	inline void reset() {
		if (this->counter) {
			if (this->counter->releaseWeakRef()) {
				delete this->counter;
			}
			this->counter = nullptr;
		}
	}
	inline ~WeakPtr() { this->reset(); }

	inline operator bool() const { return (this->counter && this->counter->value); }
	inline T &operator*() { return *this->counter->value; }
	inline T const &operator*() const { return *this->counter->value; }
	inline T *operator->() { return this->counter->value; }
	inline T const *operator->() const { return this->counter->value; }
	inline T *get() const { return this->counter->value; }
};