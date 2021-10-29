#pragma once

#include <modutils.h>
#include "AttributeIds.h"

class AttributeInstance {
public:
    char pad[0x84];
    float currentVal;
    float min;
    float max;
    float defaultVal;
};

class BaseAttributeMap {
public:
    AttributeInstance* getMutableInstance(unsigned int id);
};

class AttributeInstanceHandle {
public:
    int id;
    char pad[0x4];
    BaseAttributeMap *source;
};

static_assert(sizeof(AttributeInstanceHandle) == 0x10);

class AttributeInstanceDelegate {
public:
    char pad[0x8];
    AttributeInstanceHandle mAttributeHandle;
};

static_assert(sizeof(AttributeInstanceDelegate) == 0x18);

class HealthAttributeDelegate {
public:
    char pad1[0x18]; // base class AttributeInstanceDelegate
    uint32_t mTickCounter;
    char pad2[0x4];
    class Mob* mMob;
 };

AttributeInstance* getAttribute(class Actor* actor, unsigned int id) {
    auto attributes = direct_access<BaseAttributeMap*>(actor, 0x438);
    return attributes->getMutableInstance(id);
}