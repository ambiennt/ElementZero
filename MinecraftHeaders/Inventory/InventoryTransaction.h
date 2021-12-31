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

	//BUILD_ACCESS_MUT(enum InventorySourceType, type, 0x0); // mType
	//BUILD_ACCESS_MUT(enum ContainerID, container, 0x4); // mContainerId
	//BUILD_ACCESS_MUT(enum InventorySourceFlags, flags, 0x8); // mFlags
	
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

	BUILD_ACCESS_MUT(class InventorySource, source, 0x0); // mSource
	BUILD_ACCESS_MUT(uint32_t, slot, 0xC); // mSlot
	BUILD_ACCESS_MUT(ItemStack, from, 0x10); // mFromItem
	BUILD_ACCESS_MUT(ItemStack, to, 0xA0); // mToItem
};

class InventoryTransactionItemGroup {
public:

	BUILD_ACCESS_MUT(int32_t, itemId, 0x0); // mItemId
	BUILD_ACCESS_MUT(int32_t, itemAux, 0x4); // mItemAux
	BUILD_ACCESS_MUT(std::unique_ptr<class CompoundTag>, tag, 0x8); // mTag
	BUILD_ACCESS_MUT(int32_t, count, 0x10); // mCount
	BUILD_ACCESS_MUT(bool, overflow, 0x14); // mOverflow

	MCAPI InventoryTransactionItemGroup(ItemStack const &, int);
	inline ~InventoryTransactionItemGroup() {}
};

class InventoryTransaction {
public:

	using actionMap = std::unordered_map<class InventorySource, std::vector<class InventoryAction>>;
	BUILD_ACCESS_MUT(actionMap, actions, 0x0); // mActions

	BUILD_ACCESS_MUT(std::vector<class InventoryTransactionItemGroup>, items, 0x40); // mContents

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

class ComplexInventoryTransaction {
public:
	enum class Type {
		NORMAL            = 0,
		MISMATCH          = 1,
		ITEM_USE          = 2,
		ITEM_USE_ON_ACTOR = 3,
		RELEASE_ITEM      = 4
	};

	BUILD_ACCESS_MUT(enum Type, type, 0x8); // mType
	BUILD_ACCESS_MUT(class InventoryTransaction, data, 0x10); // mTransaction

	inline virtual ~ComplexInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

class ItemUseInventoryTransaction : public ComplexInventoryTransaction {
public:
	enum class ActionType {
		PLACE   = 0,
		USE     = 1,
		DESTROY = 2
	};

	BUILD_ACCESS_MUT(enum ActionType, actionType, 0x68); // mActionType
	BUILD_ACCESS_MUT(class BlockPos, pos, 0x6C); // mPos (NetworkBlockPosition)
	BUILD_ACCESS_MUT(uint32_t, block_runtime_id, 0x78); // mTargetBlockRuntimeId
	BUILD_ACCESS_MUT(uint8_t, face, 0x7C); // mFace
	BUILD_ACCESS_MUT(int32_t, slot, 0x80); // mSlot
	BUILD_ACCESS_MUT(class ItemStack, itemInHand, 0x88); // mItemInHand
	BUILD_ACCESS_MUT(class Vec3, clickPos, 0x124); // mClickPos

	inline virtual ~ItemUseInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

class ItemUseOnActorInventoryTransaction : public ComplexInventoryTransaction {
public:

	enum class ActionType {
		INTERACT      = 0,
		ATTACK        = 1,
		ITEM_INTERACT = 2
	};

	BUILD_ACCESS_MUT(class ActorRuntimeID, actorId, 0x68); // mRuntimeId
	BUILD_ACCESS_MUT(enum ActionType, actionType, 0x70); // mActionType
	BUILD_ACCESS_MUT(int32_t, slot, 0x74); // mSlot
	BUILD_ACCESS_MUT(class ItemStack, itemInHand, 0x78); // mItemInHand
	BUILD_ACCESS_MUT(class Vec3, playerPos, 0x108); // mPlayerPos
	BUILD_ACCESS_MUT(class Vec3, clickPos, 0x114); // mClickPos

	inline virtual ~ItemUseOnActorInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};

class ItemReleaseInventoryTransaction : public ComplexInventoryTransaction {
public:

	enum class ActionType {
		RELEASE = 0,
		USE     = 1
	};

	BUILD_ACCESS_MUT(ActionType, actionType, 0x68); // mActionType
	BUILD_ACCESS_MUT(int32_t, slot, 0x6C); // mSlot
	BUILD_ACCESS_MUT(class ItemStack, itemInHand, 0x70); // mItemInHand
	BUILD_ACCESS_MUT(class Vec3, playerPos, 0x100); // mPlayerPos

	inline virtual ~ItemReleaseInventoryTransaction() {}
	MCAPI virtual void read(ReadOnlyBinaryStream &);
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual InventoryTransactionError handle(Player &, bool) const;
	MCAPI virtual void onTransactionError(Player &, InventoryTransactionError) const;
};