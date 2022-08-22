#pragma once

#include <utility>
#include "SharedCounter.h"

template <typename T>
class SharedPtr {
public:
	SharedCounter<T> *counter;

	inline SharedPtr() : counter(nullptr) {}
	inline SharedPtr(T *inp) : counter{new SharedCounter<T>(inp)} { this->counter->addSharedRef(); }
	template <typename... ps> static inline SharedPtr make(ps &&... p) { return {new T{std::forward<ps>(p)...}}; }
	inline operator bool() const { return this->counter && this->counter->value; }
	inline T &operator*() { return *this->counter->value; }
	inline T *operator->() { return this->counter->value; }
	inline T *get() const { return this->counter->value; }
	inline void reset() {
		if (this->counter) {
			if (this->counter->releaseSharedRef()) {
				delete this->counter;
			}
			this->counter = nullptr;
		}
	}
	~SharedPtr() { this->reset(); }
};