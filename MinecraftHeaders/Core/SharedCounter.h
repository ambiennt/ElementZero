#pragma once

#include <atomic>
#include <cstdint>

template <typename T>
class SharedCounter {
public:
	T *value;
	std::atomic<int32_t> shared, weak;

	inline SharedCounter() : value(nullptr), shared(0), weak(0) {}
	inline SharedCounter(T *value) : value(value), shared(0), weak(0) {}

	inline void addSharedRef() { this->shared++; }
	inline bool releaseSharedRef() {
		this->shared--;
		if (this->shared > 0) { return false; }
		if (this->value) {
			auto temp = value;
			this->value = nullptr;
			delete temp;
		}
		return (this->weak <= 0);
	}
	inline void addWeakRef() { this->weak++; }
	inline bool releaseWeakRef() {
		this->weak--;
		return ((this->weak <= 0) && this->value);
	}
};