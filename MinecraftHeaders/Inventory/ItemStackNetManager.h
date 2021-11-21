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
};

class ItemStackNetManagerServer : public ItemStackNetManagerBase {
public:
	std::unique_ptr<ItemStackRequestActionHandler> mRequestActionHandler;
	bool mRetainSetItemStackNetIdVariants;
};