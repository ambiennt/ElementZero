#pragma once

#include <string>
#include "../Core/HashedString.h"
#include "ActorType.h"
#include "../dll.h"

struct ActorDefinitionIdentifier {
	std::string mNamespace;      // 0x0
	std::string mIdentifier;     // 0x20
	std::string mInitEvent;      // 0x40
	std::string mFullName;       // 0x60
	HashedString mCanonicalName; // 0x80

public:
	inline HashedString const &getCanonicalHash() const { return this->mCanonicalName; }
	inline std::string const &getCanonicalName() const { return this->mCanonicalName.getString(); }
	inline std::string const &getFullName() const { return this->mFullName; }
	inline std::string const &getIdentifier() const { return this->mIdentifier; }
	inline std::string const &getInitEvent() const { return this->mInitEvent; }
	inline std::string const &getNamespace() const { return this->mNamespace; }
	inline bool isEmpty() const { return this->mNamespace.empty() && this->mIdentifier.empty(); }
	inline bool isVanilla() const { return this->mNamespace == "minecraft"; }
	inline void setIdentifier(std::string const &id) { this->mIdentifier = id; }
	inline void setInitEvent(std::string const &e) { this->mInitEvent = e; }

	MCAPI ActorDefinitionIdentifier(ActorDefinitionIdentifier const &);
	MCAPI ActorDefinitionIdentifier(ActorDefinitionIdentifier &&);
	// "minecraft:entity_spawned", minecraft:entity_born", or "minecraft:entity_transformed" for initEvent
	MCAPI ActorDefinitionIdentifier(std::string ns, std::string identifier, std::string event);
	MCAPI ActorDefinitionIdentifier(std::string const & fullName);
	MCAPI ActorDefinitionIdentifier(ActorType);
	inline ActorDefinitionIdentifier() {}
	MCAPI ActorDefinitionIdentifier &operator=(ActorDefinitionIdentifier const &);
	MCAPI bool operator==(ActorDefinitionIdentifier const &);
};

static_assert(sizeof(ActorDefinitionIdentifier) == 0xA8);