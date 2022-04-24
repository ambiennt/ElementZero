#pragma once

#include <memory>

#include "../dll.h"

class BlockSource;
class BlockActor;
class BlockPos;
class Block;
class Actor;
struct ActorBlockSyncMessage;

class BlockSourceListener {
public:
	virtual ~BlockSourceListener();
	virtual void onSourceCreated(BlockSource &);
	virtual void onSourceDestroyed(BlockSource &);
	virtual void onAreaChanged(BlockSource &, BlockPos const&, BlockPos const&);
	virtual void onBlockChanged(BlockSource &, BlockPos const&, uint32_t,
		Block const&, Block const&, int32_t, ActorBlockSyncMessage const*);
	virtual void onBrightnessChanged(BlockSource &, BlockPos const&);
	virtual void onBlockEntityChanged(BlockSource &, BlockActor &);
	virtual void onBlockEntityAboutToBeRemoved(BlockSource &, std::shared_ptr<BlockActor>);
	virtual void onEntityChanged(BlockSource &, Actor &);
	virtual void onBlockEvent(BlockSource &, int32_t, int32_t, int32_t, int32_t, int32_t);
};
