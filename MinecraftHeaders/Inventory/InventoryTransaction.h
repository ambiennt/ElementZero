#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>

#include "../Core/NBT.h"
#include "../Core/Packet.h"
#include "../Core/ContainerID.h"
#include "../Container/ContainerEnumName.h"
#include "../Math/NetworkBlockPosition.h"
#include "../Math/BlockFace.h"
#include "../Actor/Player.h"
#include "../Actor/ActorRuntimeID.h"
#include "../Item/ItemStack.h"
#include "../Item/SimpleClientNetId.h"
#include "../dll.h"

class ReadOnlyBinaryStream;
class BinaryStream;
class ItemStack;
class CompoundTag;

enum class InventoryTransactionError {
	Unknown             = 0,
	NoError             = 1,
	BalanceMismatch     = 2,
	SourceItemMismatch  = 3,
	InventoryMismatch   = 4,
	SizeMismatch        = 5,
	AuthorityMismatch   = 6,
	StateMismatch       = 7, // Unexcepted
	ApiDenied           = 8
};

enum class InventorySourceType {
	Invalid                = -1,
	Container              = 0,
	Global                 = 1,
	WorldInteraction       = 2,
	Creative               = 3,
	UntrackedInteractionUI = 100,
	NONIMPLEMENTEDTODO     = 99999 // .give
};

class InventorySource {
public:
	InventorySourceType type = InventorySourceType::Invalid;
	ContainerID container    = ContainerID::Invalid;
	enum class InventorySourceFlags { NoFlag, WorldInteraction_Random } flags;

	inline InventorySource(ContainerID id) : container(id) {}
	inline InventorySource(InventorySourceType type) : type(type) {}
	inline InventorySource(InventorySourceType type, InventorySourceFlags flags) : type(type), flags(flags) {}
	inline InventorySource(InventorySourceType type, ContainerID id) : type(type), container(id) {}

	constexpr inline bool operator==(InventorySource const &rhs) const noexcept {
		return type == rhs.type && container == rhs.container && flags == rhs.flags;
	}

	static inline InventorySource fromContainerWindowID(ContainerID id) { return {id}; }
	static inline InventorySource fromCreativeInventory() { return {InventorySourceType::Creative}; }
	static inline InventorySource fromGlobalInventory() { return {InventorySourceType::Global}; }
	static inline InventorySource fromWorldInteraction(InventorySourceFlags flags) {
		return {InventorySourceType::WorldInteraction, flags};
	}
	static inline InventorySource fromInvalid() { return {InventorySourceType::Invalid}; }
	static inline InventorySource fromUntrackedInteractionUI(ContainerID id) {
		return {InventorySourceType::UntrackedInteractionUI, id};
	}
	static inline InventorySource fromNONIMPLEMENTEDTODO(ContainerID id) {
		return {InventorySourceType::NONIMPLEMENTEDTODO, id};
	}
};

namespace std {
template <> struct hash<InventorySource> {
	constexpr uint64_t operator()(InventorySource const &source) const noexcept {
		return (uint64_t) source.type << 16 ^ (uint64_t) source.container;
	}
};
} // namespace std

class InventoryAction {
public:
	InventorySource source;
	unsigned int slot = 0;
	ItemStack from, to;
};

class InventoryTransactionItemGroup {
public:
	unsigned short itemId  = 0;
	unsigned short itemAux = 0;
	std::unique_ptr<CompoundTag> tag;
	int count          = 0;
	bool overflow      = false;

	MCAPI InventoryTransactionItemGroup(ItemStack const &, int);
	inline ~InventoryTransactionItemGroup() {}
};

class InventoryTransaction {
public:
	std::unordered_map<InventorySource, std::vector<InventoryAction>> actions;
	std::vector<InventoryTransactionItemGroup> items;

	MCAPI void addAction(InventoryAction const &);
	MCAPI InventoryTransactionError executeFull(Player &, bool) const;
	MCAPI void forceBalanceTransaction();
	MCAPI std::vector<InventoryAction> const &getActions(InventorySource const &) const;
	MCAPI
	std::function<InventoryTransactionError(Player &, InventoryAction const &, bool)>
	getVerifyFunction(InventorySource const &) const;
	MCAPI InventoryTransactionError verifyFull(Player &, bool) const;

private:
	MCAPI void addActionToContent(InventoryAction const &);
	MCAPI void _dropCreatedItems(Player &);
	MCAPI void addItemToContent(ItemStack const &);

public:
	inline InventoryTransaction() {}
	inline InventoryTransaction(std::vector<InventoryAction> actions) {
		for (auto &act : actions) addAction(act);
	}
};

static_assert(offsetof(InventoryTransaction, items) == 64);

class ComplexInventoryTransaction {
public:
	enum class Type : unsigned {
		NORMAL            = 0,
		MISMATCH          = 1,
		ITEM_USE          = 2,
		ITEM_USE_ON_ACTOR = 3,
		RELEASE_ITEM      = 4,
	} type;
	InventoryTransaction data;

	inline virtual ~ComplexInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

static_assert(sizeof(ComplexInventoryTransaction) == 104);

class ItemUseInventoryTransaction : public ComplexInventoryTransaction {
public:
	enum class Type { USE_ITEM_ON, USE_ITEM, DESTROY } actionType;
	NetworkBlockPosition pos;
	uint32_t block_runtime_id;
	BlockFace face;
	uint32_t slot;
	ItemStack itemInHand;
	Vec3 playerPos, clickPos;

	inline virtual ~ItemUseInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

static_assert(offsetof(ItemUseInventoryTransaction, itemInHand) == 136);
static_assert(offsetof(ItemUseInventoryTransaction, playerPos) == 280);
static_assert(offsetof(ItemUseInventoryTransaction, clickPos) == 292);
static_assert(sizeof(ItemUseInventoryTransaction) == 304);

class ItemUseOnActorInventoryTransaction : public ComplexInventoryTransaction {
public:
	ActorRuntimeID actorId;
	int actionType;
	uint32_t slot;
	ItemStack itemInHand;
	Vec3 playerPos, clickPos;

	inline virtual ~ItemUseOnActorInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

static_assert(offsetof(ItemUseOnActorInventoryTransaction, playerPos) == 264);
static_assert(offsetof(ItemUseOnActorInventoryTransaction, clickPos) == 276);

class ItemReleaseInventoryTransaction : public ComplexInventoryTransaction {
public:
	int actionType;
	uint32_t slot;
	ItemStack itemInHand;
	Vec3 playerPos;

	inline virtual ~ItemReleaseInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

static_assert(offsetof(ItemReleaseInventoryTransaction, playerPos) == 256);
