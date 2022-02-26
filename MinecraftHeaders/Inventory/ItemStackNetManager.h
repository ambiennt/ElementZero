#pragma once

#include <modutils.h>
#include "InventoryTransaction.h"
#include "ContainerScreenContext.h"
#include "../Container/ContainerEnumName.h"
#include "../Container/ContainerType.h"
#include "../Item/ItemStackNetIdVariant.h"
#include "../dll.h"

#include <memory>

class ItemStackRequestAction {
public:
	BUILD_ACCESS_MUT(uint8_t, mActionType, 0x8); // char array of size 1
};

struct ItemStackRequestSlotInfo {
	BUILD_ACCESS_MUT(enum ContainerEnumName, mOpenContainerNetId, 0x0);
	BUILD_ACCESS_MUT(uint8_t, mSlot, 0x1);
	BUILD_ACCESS_MUT(class ItemStackNetIdVariant, mNetIdVariant, 0x4);
};

class ItemStackRequestActionTransferBase : public ItemStackRequestAction {
public:
	BUILD_ACCESS_MUT(bool, mIsDstSerialized, 0x10);
	BUILD_ACCESS_MUT(bool, mIsAmountSerialized, 0x11);
	BUILD_ACCESS_MUT(uint8_t, mAmount, 0x12);
	BUILD_ACCESS_MUT(struct ItemStackRequestSlotInfo, mSrc, 0x14);
	BUILD_ACCESS_MUT(struct ItemStackRequestSlotInfo, mDst, 0x20);
};

class ItemStackNetManagerBase {
public:
	BUILD_ACCESS_MUT(bool, mIsEnabled, 0x8);
	BUILD_ACCESS_MUT(bool, mIsClientSide, 0x9);
	BUILD_ACCESS_MUT(class Player *, mPlayer, 0x10);
	BUILD_ACCESS_MUT(class ContainerScreenContext, mScreenContext, 0x18);
	BUILD_ACCESS_MUT(bool, mCurrentRequestHasCraftAction, 0x40);
	//BUILD_ACCESS_MUT(SimpleClientNetId<ItemStackLegacyRequestIdTag, int32_t, 0>, mLegacyTransactionRequestId, 0x44);

	virtual ~ItemStackNetManagerBase();
	virtual bool isEnabled(void);
	virtual int getRequestId(void);
	virtual void retainSetItemStackNetIdVariant(void);
	virtual bool allowInventoryTransactionManager(void);
	virtual void _tryBeginClientLegacyTransactionRequest(void);
	virtual void onContainerScreenOpen(class ContainerScreenContext const&);
	virtual void onContainerScreenClose(void);
	virtual void initOpenContainer(class BlockSource&, enum ContainerEnumName, struct ContainerWeakRef const&);
	virtual void _addLegacyTransactionRequestSetItemSlot(enum ContainerType, int32_t slot);

	inline bool isScreenOpen(void) {
		auto& ctx = this->mScreenContext;
		return ctx.mPlayer && (ctx.mScreenContainerType != ContainerType::NONE) && (ctx.mOwner.index() != 0);
	}
};

class ItemStackNetManagerServer : public ItemStackNetManagerBase {
public:
	BUILD_ACCESS_MUT(std::unique_ptr<class ItemStackRequestActionHandler>, mRequestActionHandler, 0x48);
	BUILD_ACCESS_MUT(bool, mRetainSetItemStackNetIdVariants, 0x50);
};

class ItemStackRequestActionHandler {
public:
	int8_t pad[0x38]; // ItemStackRequestActionCraftHandler
	BUILD_ACCESS_MUT(class Player *, mPlayer, 0x38);
	BUILD_ACCESS_MUT(class ItemStackNetManagerServer *, mItemStackNetManager, 0x40);
	// TODO
};