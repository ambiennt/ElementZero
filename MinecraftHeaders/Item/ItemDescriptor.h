#pragma once

#include "../dll.h"

class ItemDescriptor {
public:
    std::weak_ptr<class Item> mItem{};
    class Block* mBlock{};
    unsigned short mAuxValue{};
    bool mValid{};
};