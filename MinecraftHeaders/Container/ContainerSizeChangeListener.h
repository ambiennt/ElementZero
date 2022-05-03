#pragma once

class ContainerSizeChangeListener {
public:
	virtual void ContainerSizeChanged(int) = 0;
	virtual ~ContainerSizeChangeListener();
};