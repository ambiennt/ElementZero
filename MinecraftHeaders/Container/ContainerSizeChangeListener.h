#pragma once

class ContainerSizeChangeListener {
public:
	virtual void ContainerSizeChanged(int32_t) = 0;
	virtual ~ContainerSizeChangeListener();
};