#pragma once

#include "../dll.h"

namespace Json {
class Value;
}

class ProjectileComponent;
class Actor;

class OnHitSubcomponent {
public:
	virtual ~OnHitSubcomponent();
	virtual void readfromJSON(Json::Value &value);
	virtual void writetoJSON(Json::Value &value);
	virtual void doOnHitEffect(Actor &owner, ProjectileComponent &component);
};

class TeleportToSubcomponent : public OnHitSubcomponent {
public:
};