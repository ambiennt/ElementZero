#pragma once

#include "../Core/json.h"
#include "ProjectileComponent.h"

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