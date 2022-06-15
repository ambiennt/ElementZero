#pragma once

#include <vector>
#include <memory>

template <typename T> class CommandSelectorResults {
	std::shared_ptr<std::vector<T *>> data;

public:
	inline auto begin() { return this->data->begin(); }
	inline auto end() { return this->data->end(); }
	inline size_t count() const { return this->data->size(); }
	inline bool empty() const { return this->data->empty(); }
};