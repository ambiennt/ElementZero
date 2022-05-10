#pragma once

class ContainerContentChangeListener {
public:
	virtual void ContainerContentChanged(int32_t) = 0;
	virtual ~ContainerContentChangeListener();
};