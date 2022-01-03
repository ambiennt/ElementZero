#pragma once

#include "FillingContainer.h"
#include "RandomizableBlockActorContainerBase.h"

class RandomizableBlockActorFillingContainer : public RandomizableBlockActorContainerBase, public FillingContainer {
public:
	MCAPI RandomizableBlockActorFillingContainer(
		enum BlockActorType blockEntityType, std::string const& id, class BlockPos const& pos, int numTotalSlots, enum ContainerType containerType);

	virtual ~RandomizableBlockActorFillingContainer();
	virtual void setContainerChanged(int) override;
	virtual void startOpen(class Player&) override;
	virtual void dropContents(class BlockSource&, class Vec3 const&, bool) override;
	virtual void initializeContainerContents(class BlockSource&) override;
};