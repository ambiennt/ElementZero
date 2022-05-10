#pragma once

#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>

#include "../Core/NBT.h"
#include "../Core/Packet.h"
#include "../Container/ContainerID.h"
#include "../Container/ContainerEnumName.h"
#include "../Math/NetworkBlockPosition.h"
#include "../Actor/Player.h"
#include "../Actor/ActorRuntimeID.h"
#include "../Item/ItemStack.h"
#include "../Item/SimpleClientNetId.h"
#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

#include <modutils.h>


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
	enum class InventorySourceFlags {
		NoFlag                  = 0,
		WorldInteraction_Random = 1
	};

	InventorySourceType type = InventorySourceType::Invalid; // keep as normal fields so we can use initializer lists
	ContainerID container    = ContainerID::Invalid;
	InventorySourceFlags flags;

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

static_assert(offsetof(InventorySource, type) == 0x0);
static_assert(offsetof(InventorySource, container) == 0x4);
static_assert(offsetof(InventorySource, flags) == 0x8);

namespace std {
template <> struct hash<InventorySource> {
	constexpr uint64_t operator()(InventorySource const &source) const noexcept {
		return (uint64_t) source.type << 16 ^ (uint64_t) source.container;
	}
};
} // namespace std

class InventoryAction {
public:

	InventorySource source; // 0x0
	uint32_t slot; // 0xC - idk why this is unsigned
	ItemStack from, to; // 0x10, 0xA0
};

static_assert(offsetof(InventoryAction, source) == 0x0);
static_assert(offsetof(InventoryAction, slot) == 0xC);
static_assert(offsetof(InventoryAction, from) == 0x10);
static_assert(offsetof(InventoryAction, to) == 0xA0);

class InventoryTransactionItemGroup {
public:

	int32_t itemId; // 0x0
	int32_t itemAux; // 0x4
	std::unique_ptr<CompoundTag> tag; // 0x8
	int32_t count; // 0x10
	bool overflow; // 0x14

	MCAPI InventoryTransactionItemGroup(ItemStack const &, int);
	inline ~InventoryTransactionItemGroup() {}
};

static_assert(offsetof(InventoryTransactionItemGroup, itemId) == 0x0);
static_assert(offsetof(InventoryTransactionItemGroup, itemAux) == 0x4);
static_assert(offsetof(InventoryTransactionItemGroup, tag) == 0x8);
static_assert(offsetof(InventoryTransactionItemGroup, count) == 0x10);
static_assert(offsetof(InventoryTransactionItemGroup, overflow) == 0x14);

class InventoryTransaction {
public:

	std::unordered_map<class InventorySource, std::vector<class InventoryAction>> actions; // 0x0
	std::vector<class InventoryTransactionItemGroup> items; // 0x40

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

static_assert(offsetof(InventoryTransaction, actions) == 0x0);
static_assert(offsetof(InventoryTransaction, items) == 0x40);

class ComplexInventoryTransaction {
public:
	enum class Type {
		NORMAL            = 0,
		MISMATCH          = 1,
		ITEM_USE          = 2,
		ITEM_USE_ON_ACTOR = 3,
		RELEASE_ITEM      = 4
	};

	Type type; // 0x8
	InventoryTransaction data; // 0x10

	inline virtual ~ComplexInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

static_assert(offsetof(ComplexInventoryTransaction, type) == 0x8);
static_assert(offsetof(ComplexInventoryTransaction, data) == 0x10);

class ItemUseInventoryTransaction : public ComplexInventoryTransaction {
public:
	enum class ActionType {
		PLACE   = 0,
		USE     = 1,
		DESTROY = 2
	};

	ActionType actionType; // 0x68
	BlockPos pos; // 0x6C
	uint32_t block_runtime_id; // 0x78
	uint8_t face; // 0x7C
	int32_t slot; // 0x80
	ItemStack itemInHand; // 0x88
	Vec3 playerPos, clickPos; // 0x124

	inline virtual ~ItemUseInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

static_assert(offsetof(ItemUseInventoryTransaction, actionType) == 0x68);
static_assert(offsetof(ItemUseInventoryTransaction, pos) == 0x6C);
static_assert(offsetof(ItemUseInventoryTransaction, block_runtime_id) == 0x78);
static_assert(offsetof(ItemUseInventoryTransaction, face) == 0x7C);
static_assert(offsetof(ItemUseInventoryTransaction, slot) == 0x80);
static_assert(offsetof(ItemUseInventoryTransaction, itemInHand) == 0x88);
static_assert(offsetof(ItemUseInventoryTransaction, playerPos) == 0x118);
static_assert(offsetof(ItemUseInventoryTransaction, clickPos) == 0x124);

class ItemUseOnActorInventoryTransaction : public ComplexInventoryTransaction {
public:

	enum class ActionType {
		INTERACT      = 0,
		ATTACK        = 1,
		ITEM_INTERACT = 2
	};

	ActorRuntimeID actorId; // 0x68
	ActionType actionType; // 0x70
	int32_t slot; // 0x74
	ItemStack itemInHand; // 0x78
	Vec3 playerPos, clickPos; // 0x108, 0x114

	inline virtual ~ItemUseOnActorInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

static_assert(offsetof(ItemUseOnActorInventoryTransaction, actorId) == 0x68);
static_assert(offsetof(ItemUseOnActorInventoryTransaction, actionType) == 0x70);
static_assert(offsetof(ItemUseOnActorInventoryTransaction, slot) == 0x74);
static_assert(offsetof(ItemUseOnActorInventoryTransaction, itemInHand) == 0x78);
static_assert(offsetof(ItemUseOnActorInventoryTransaction, playerPos) == 0x108);
static_assert(offsetof(ItemUseOnActorInventoryTransaction, clickPos) == 0x114);

class ItemReleaseInventoryTransaction : public ComplexInventoryTransaction {
public:

	enum class ActionType {
		RELEASE = 0,
		USE     = 1
	};

	ActionType actionType; // 0x68
	int32_t slot; // 0x6C
	ItemStack itemInHand; // 0x70
	Vec3 playerPos; // 0x100

	inline virtual ~ItemReleaseInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

static_assert(offsetof(ItemReleaseInventoryTransaction, actionType) == 0x68);
static_assert(offsetof(ItemReleaseInventoryTransaction, slot) == 0x6C);
static_assert(offsetof(ItemReleaseInventoryTransaction, itemInHand) == 0x70);
static_assert(offsetof(ItemReleaseInventoryTransaction, playerPos) == 0x100);