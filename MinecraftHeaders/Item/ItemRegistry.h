#pragma once

#include "../dll.h"
#include "../Core/HashedString.h"
#include "../Core/WeakPtr.h"
#include "../Core/SharedPtr.h"
#include "../Item/Item.h"
#include "../Item/ItemRuntimeID.h"

#include <unordered_map>
#include <vector>

class ItemRegistry {
	MCAPI static std::unordered_map<HashedString, HashedString> mItemAliasLookupMap;
	MCAPI static std::unordered_map<int32_t, WeakPtr<Item>> mIdToItemMap;
	MCAPI static std::unordered_map<HashedString, WeakPtr<Item>> mNameToItemMap;
	MCAPI static std::vector<SharedPtr<Item>> mItemRegistry;
	MCAPI static int16_t mMaxItemID;
public:
	inline std::unordered_map<HashedString, HashedString>& getItemAliasLookupMap() const {
		return mItemAliasLookupMap;
	}
	inline std::unordered_map<int32_t, WeakPtr<Item>>& getIdToItemMap() const {
		return mIdToItemMap;
	}
	inline std::unordered_map<HashedString, WeakPtr<Item>>& getNameToItemMap() const {
		return mNameToItemMap;
	}

	// inString can be with or without "minecraft:"
	MCAPI static WeakPtr<Item> lookupByName(int32_t &outItemId, int32_t &outItemAux, const std::string& inString);
	MCAPI static WeakPtr<Item> lookupByName(int32_t &outItemAux, const std::string& inString);
	static inline WeakPtr<Item> lookupByName(const std::string& inString) {
		int32_t outItemId, outItemAux;
		return lookupByName(outItemId, outItemAux, inString);
	}

	MCAPI static WeakPtr<Item> getItem(int16_t id);
	static inline WeakPtr<Item> getItem(ItemRuntimeID id) {
		return getItem((int16_t)id);
	}
	static inline WeakPtr<Item> getItem(const BlockLegacy& legacy) {
		return getItem(legacy.toItemId());
	}
	static inline WeakPtr<Item> getItem(const Block* block) {
		return getItem(block->mLegacyBlock->toItemId());
	}

	static inline int32_t getItemCount() {
		return mItemRegistry.size();
	}
};