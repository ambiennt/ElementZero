#pragma once

#include <modutils.h>
#include "InventoryTransaction.h"
#include "ContainerScreenContext.h"
#include "../Container/ContainerEnumName.h"
#include "../Item/ItemStackNetIdVariant.h"
#include "../dll.h"

#include <memory>

struct ItemStackRequestSlotInfo {
	ContainerEnumName mOpenContainerNetId;
	uint8_t mSlot;
	ItemStackNetIdVariant mNetIdVariant;
};

class ItemStackRequestAction {
public:
	uint8_t mActionType; // char array of size 1
};

class ItemStackRequestActionTransferBase : public ItemStackRequestAction {
public:
	bool mIsDstSerialized;
	bool mIsAmountSerialized;
	uint8_t mAmount;
	ItemStackRequestSlotInfo mSrc;
	ItemStackRequestSlotInfo mDst;
};

class ItemStackRequestActionHandler;

class ItemStackNetManagerBase {
public:
	bool mIsEnabled;
	bool mIsClientSide;
	Player* mPlayer;
	ContainerScreenContext mScreenContext;
	bool mCurrentRequestHasCraftAction;
	SimpleClientNetId<ItemStackLegacyRequestIdTag, int32_t, 0> mLegacyTransactionRequestId;

	virtual ~ItemStackNetManagerBase();
    virtual bool isEnabled(void);
    virtual int getRequestId(void);
    virtual void retainSetItemStackNetIdVariant(void);
    virtual bool allowInventoryTransactionManager(void);
    virtual void _tryBeginClientLegacyTransactionRequest(void);
    virtual void onContainerScreenOpen(class ContainerScreenContext const&);
    virtual void onContainerScreenClose(void);
    virtual void initOpenContainer(class BlockSource&, enum ContainerEnumName, struct ContainerWeakRef const&);
    virtual void _addLegacyTransactionRequestSetItemSlot(enum ContainerType, int);
};

class ItemStackNetManagerServer : public ItemStackNetManagerBase {
public:
	std::unique_ptr<ItemStackRequestActionHandler> mRequestActionHandler;
	bool mRetainSetItemStackNetIdVariants;
};