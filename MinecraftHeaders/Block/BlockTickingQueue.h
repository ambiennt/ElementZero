#pragma once

#include "../Level/Tick.h"
#include "../dll.h"
#include <cstdint>

class LevelChunk;

enum class TickingQueueType : int8_t {
    Internal = 0,
    Random = 1,
};

class BlockTickingQueue {
public:
    LevelChunk *mOwningChunk; // 0x8
    Tick mCurrentTick; // 0x8
    //BlockTickingQueue::TickDataSet mNextTickQueue; // TODO - 0x10
    //BlockTickingQueue::TickDataSet mActiveTickQueue; // TODO - 0x28
    uint8_t pad[0x30];
    TickingQueueType mQueueType; // 0x40
    bool mInstaTick; // 0x41
};

static_assert(offsetof(BlockTickingQueue, mInstaTick) == 0x41);
static_assert(sizeof(BlockTickingQueue) == 0x48);