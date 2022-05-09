#pragma once

#include "InventoryTransaction.h"
#include "ContainerScreenContext.h"
#include "../Container/ContainerEnumName.h"
#include "../Container/ContainerType.h"
#include "../Item/ItemStackNetIdVariant.h"
#include "../dll.h"

#include <memory>

class ItemStackRequestActionCraftBase;
class ItemStackRequestActionHandler;
class SparseContainer;
class ContainerWeakRef;
class BlockSource;

enum class ItemStackRequestActionType : int8_t {
	Take = 0x0,
	Place = 0x1,
	Swap = 0x2,
	Drop = 0x3,
	Destroy = 0x4,
	Consume = 0x5,
	Create = 0x6,
	LabTableCombine = 0x7,
	BeaconPayment = 0x8,
	CraftRecipe = 0x9,
	CraftRecipeAuto = 0xA,
	CraftCreative = 0xB,
	CraftNonImplemented_DEPRECATEDASKTYLAING = 0xC, // ...
	CraftResults_DEPRECATEDASKTYLAING = 0xD, // ...
};

class ItemStackRequestAction {
public:
	virtual ~ItemStackRequestAction();
	virtual const ItemStackRequestActionCraftBase *getCraftAction() const;
protected:
	virtual void _write(BinaryStream &) const;
	virtual bool _read(ReadOnlyBinaryStream &);
public:

	ItemStackRequestActionType mActionType; // 0x8
};
static_assert(sizeof(ItemStackRequestAction) == 0x10);

struct ItemStackRequestSlotInfo {
	ContainerEnumName mOpenContainerNetId; // 0x0
	uint8_t mSlot; // 0x1
	ItemStackNetIdVariant mNetIdVariant; // 0x4
};
static_assert(sizeof(ItemStackRequestSlotInfo) == 0xC);

class ItemStackRequestActionTransferBase : public ItemStackRequestAction {
public:
	bool mIsDstSerialized; // 0x10
	bool mIsAmountSerialized; // 0x11
	uint8_t mAmount; // 0x12
	ItemStackRequestSlotInfo mSrc; // 0x14
	ItemStackRequestSlotInfo mDst; // 0x20
};
static_assert(sizeof(ItemStackRequestActionTransferBase) == 0x30);

class ItemStackNetManagerBase {
public:
	bool mIsEnabled; // const - 0x8
	bool mIsClientSide; // const - 0x9
	Player* mPlayer; // 0x10
	ContainerScreenContext mScreenContext; // 0x18
	bool mCurrentRequestHasCraftAction; // 0x40
	SimpleClientNetId<ItemStackLegacyRequestIdTag, int32_t, 0> mLegacyTransactionRequestId; // 0x44

	virtual ~ItemStackNetManagerBase();
	virtual bool isEnabled();
	virtual SimpleClientNetId<ItemStackRequestIdTag, int32_t, 0> getRequestId() = 0;
	virtual bool retainSetItemStackNetIdVariant();
	virtual bool allowInventoryTransactionManager() = 0;
	//virtual gsl::final_action<std::function<void ()>> _tryBeginClientLegacyTransactionRequest();
private:
	__declspec(dllimport) virtual void* vtbl_pad_5() = 0;
public:
	virtual void onContainerScreenOpen(ContainerScreenContext const&);
	virtual void onContainerScreenClose() = 0;
	virtual SparseContainer* initOpenContainer(BlockSource&, ContainerEnumName, ContainerWeakRef const&) = 0;
	virtual void _addLegacyTransactionRequestSetItemSlot(ContainerType, int32_t slot);

	inline bool isScreenOpen() {
		auto& ctx = this->mScreenContext;
		return ctx.mPlayer && (ctx.mScreenContainerType != ContainerType::NONE) && (ctx.mOwner.index() != 0);
	}
};
static_assert(sizeof(ItemStackNetManagerBase) == 0x48);

class ItemStackNetManagerServer : public ItemStackNetManagerBase {
public:
	std::unique_ptr<ItemStackRequestActionHandler> mRequestActionHandler; // 0x48
	bool mRetainSetItemStackNetIdVariants; // 0x50
};
static_assert(sizeof(ItemStackNetManagerServer) == 0x58);

class ItemStackRequestActionHandler {
public:
	uint8_t pad1[0x38]; // TODO
	Player* mPlayer; // 0x38
	ItemStackNetManagerServer* mItemStackNetManager; // 0x40
	uint8_t pad2[0x1B8]; // TODO
};
static_assert(sizeof(ItemStackRequestActionHandler) == 0x200);