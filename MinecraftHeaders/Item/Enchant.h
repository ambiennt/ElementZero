#pragma once

#include <string>
#include <vector>

#include <modutils.h>
#include "../Core/HashedString.h"
#include "../Core/NBT.h"
#include "../dll.h"

class ActorDamageSource;
class Actor;
class Mob;
class ItemStackBase;
class ItemStack;
class Item;
class ItemInstance;
class ReadOnlyBinaryStream;
class Random;
class Vec3;
class BlockSource;

class EnchantmentInstance;
class ItemEnchants;

enum class EquipmentFilter : int32_t {
	MainHand = 0x0,
	OffHand  = 0x1,
	Hands    = 0x2,
	Armor    = 0x3,
	All      = 0x4,
	Count    = 0x5,
};

enum class EnchantResultType : int8_t {
	Fail = 0,
	Conflict = 1,
	Increment = 2,
	Enchant = 3,
};

struct EnchantResult {
	EnchantResultType result; // 0x0
	uint64_t enchantIdx;      // 0x8
	int32_t level;            // 0x10
};
static_assert(sizeof(EnchantResult) == 0x18);

class Enchant {
public:
	enum class Type : int8_t {
		protection            = 0,
		fire_protection       = 1,
		feather_falling       = 2,
		blast_protection      = 3,
		projectile_protection = 4,
		thorns                = 5,
		respiration           = 6,
		depth_strider         = 7,
		aqua_affinity         = 8,
		sharpness             = 9,
		smite                 = 10,
		bane_of_arthropods    = 11,
		knockback             = 12,
		fire_aspect           = 13,
		looting               = 14,
		efficiency            = 15,
		silk_touch            = 16,
		unbreaking            = 17,
		fortune               = 18,
		power                 = 19,
		punch                 = 20,
		flame                 = 21,
		infinity              = 22,
		luck_of_the_sea       = 23,
		lure                  = 24,
		frost_walker          = 25,
		mending               = 26,
		binding               = 27,
		vanishing             = 28,
		impaling              = 29,
		riptide               = 30,
		loyalty               = 31,
		channeling            = 32,
		multishot             = 33,
		piercing              = 34,
		quick_charge          = 35,
		soul_speed            = 36,
		num_enchantments      = 37,
		invalid_enchantment   = 38
	};

	enum class Frequency {
		VeryRare         = 1,
		Rare             = 3,
		Uncommon         = 10,
		Common           = 30
	};

	enum class Slot {
		ALL              = -1,
		NONE             = 0,
		ARMOR_HEAD       = 1,
		ARMOR_TORSO      = 2,
		ARMOR_FEET       = 4,
		ARMOR_LEGS       = 8,
		G_ARMOR          = 15,
		SWORD            = 16,
		BOW              = 32,
		HOE              = 64,
		SHEARS           = 128,
		FLINTSTEEL       = 256,
		AXE              = 512,
		PICKAXE          = 1024,
		SHOVEL           = 2048,
		G_DIGGING        = 3648,
		FISHING_ROD      = 4096,
		CARROT_STICK     = 8192,
		ELYTRA           = 16384,
		SPEAR            = 32768,
		CROSSBOW         = 65536,
		SHIELD           = 131072,
		G_TOOL           = 131520,
		COSMETIC_HEAD    = 262144,
		COMPASS          = 524288,
		MUSHROOM_STICK   = 1048576
	};

	enum class CompatibilityID : int32_t {
		NON_CONFLICT = 0x0,
		DAMAGE = 0x1,
		GATHERING = 0x2,
		PROTECTION = 0x3,
		FROSTSTRIDER = 0x4,
		MENDFINITY = 0x5,
		LOYALRIPTIDE = 0x6,
	};

	Type mEnchantType{}; // const - 0x8
	Frequency mFrequency{}; // const - 0x8
	bool mIsLootable{}; // const - 0x10
	int32_t mPrimarySlots{}; // const - 0x14
	int32_t mSecondarySlots{}; // const - 0x18
	int32_t mCompatibility{}; // const - 0x1C
	std::string mDescription; // const - 0x20
	HashedString mStringId; // const - 0x40
	bool mIsExperimental{}; // 0x68
	bool mIsDisabled{}; // 0x69

	virtual ~Enchant();
	virtual bool isCompatibleWith(Type) const;
	virtual int32_t getMinCost(int32_t) const;
	virtual int32_t getMaxCost(int32_t) const;
	virtual int32_t getMinLevel() const;
	virtual int32_t getMaxLevel() const;
	virtual int32_t getDamageProtection(int32_t, ActorDamageSource const &) const;
	virtual float getDamageBonus(int32_t, Actor const &) const;
	virtual void doPostAttack(Actor &, Actor &, int32_t) const;
	virtual void doPostHurt(ItemInstance &, Actor &, Actor &, int32_t) const;
	virtual bool isMeleeDamageEnchant() const;
	virtual bool isProtectionEnchant() const;
	virtual bool isTreasureOnly() const;
};
static_assert(sizeof(Enchant) == 0x70);

class EnchantUtils {
	MCAPI static std::vector<std::string> mEnchantmentNames;
	MCAPI static void _convertBookCheck(ItemStackBase &out);

public:
	MCAPI static std::string getEnchantNameAndLevel(Enchant::Type type, int32_t);
	MCAPI static bool applyEnchant(ItemStackBase &out, EnchantmentInstance const &enchant, bool allowNonVanilla);
	MCAPI static int32_t applyEnchant(ItemStackBase &out, ItemEnchants const &enchants, bool allowNonVanilla);
	MCAPI static int32_t getEnchantLevel(Enchant::Type enchantType, ItemStackBase const& stack);
	MCAPI static void doPostHurtEffects(Mob &victim, Mob &attacker);
	MCAPI static void doPostDamageEffects(Actor &victim, Actor &attacker);
	MCAPI static int32_t determineActivation(Enchant::Type);
	MCAPI static int32_t getBestEnchantLevel(Enchant::Type, Mob const &, EquipmentFilter);
	MCAPI static int32_t getLootableRandomEnchantIndex(Random &);
	MCAPI static EnchantResult canEnchant(ItemStackBase const &item, Enchant::Type type, int32_t level, bool allowNonVanilla);
	MCAPI static std::vector<int32_t> getEnchantCosts(ItemStackBase const &, int32_t);
	MCAPI static std::vector<Vec3> getEnchantingTablePositions(BlockSource &, Vec3 const &);
	MCAPI static void randomlyEnchant(ItemStack &, int32_t, int32_t, bool);
	MCAPI static void randomlyEnchant(ItemInstance &, int32_t, int32_t, bool);
	MCAPI static std::vector<Vec3> getBookCasePositions(BlockSource &, Vec3 const &);
	MCAPI static std::vector<int32_t> getLegalEnchants(Item const *);
	MCAPI static int32_t getMeleeDamageBonus(Actor const &victim, Actor &attacker);
	MCAPI static void appendEnchantToFormattedText(Enchant::Type, std::string const &, std::string &);
	MCAPI static ItemStack const &getRandomItemWithMending(Mob const &);
	MCAPI static ItemStack const &getRandomItemWith(Enchant::Type, Mob const &, EquipmentFilter);
	MCAPI static std::vector<EnchantmentInstance> getAvailableEnchantmentResults(Item const *, int32_t, bool);
	MCAPI static ItemEnchants selectEnchantments(Item const *, int32_t, int32_t, bool);
	MCAPI static ItemInstance generateEnchantedBook(EnchantmentInstance const &);
	MCAPI static float getDamageReduction(ActorDamageSource const &, Mob const &);
	MCAPI static bool hasEnchant(Enchant::Type, ItemStackBase const &);
	
	inline static const char* getEnchantName(Enchant::Type type) {
		switch (type) {
			case Enchant::Type::protection: return "protection";
			case Enchant::Type::fire_protection: return "fire_protection";
			case Enchant::Type::feather_falling: return "feather_falling";
			case Enchant::Type::blast_protection: return "blast_protection";
			case Enchant::Type::projectile_protection: return "projectile_protection";
			case Enchant::Type::thorns: return "thorns";
			case Enchant::Type::respiration: return "respiration";
			case Enchant::Type::depth_strider: return "depth_strider";
			case Enchant::Type::aqua_affinity: return "aqua_affinity";
			case Enchant::Type::sharpness: return "sharpness";
			case Enchant::Type::smite: return "smite";
			case Enchant::Type::bane_of_arthropods: return "bane_of_arthropods";
			case Enchant::Type::knockback: return "knockback";
			case Enchant::Type::fire_aspect: return "fire_aspect";
			case Enchant::Type::looting: return "looting";
			case Enchant::Type::efficiency: return "efficiency";
			case Enchant::Type::silk_touch: return "silk_touch";
			case Enchant::Type::unbreaking: return "unbreaking";
			case Enchant::Type::fortune: return "fortune";
			case Enchant::Type::power: return "power";
			case Enchant::Type::punch: return "punch";
			case Enchant::Type::flame: return "flame";
			case Enchant::Type::infinity: return "infinity";
			case Enchant::Type::luck_of_the_sea: return "luck_of_the_sea";
			case Enchant::Type::lure: return "lure";
			case Enchant::Type::frost_walker: return "frost_walker";
			case Enchant::Type::mending: return "mending";
			case Enchant::Type::binding: return "binding";
			case Enchant::Type::vanishing: return "vanishing";
			case Enchant::Type::impaling: return "impaling";
			case Enchant::Type::riptide: return "riptide";
			case Enchant::Type::loyalty: return "loyalty";
			case Enchant::Type::channeling: return "channeling";
			case Enchant::Type::multishot: return "multishot";
			case Enchant::Type::piercing: return "piercing";
			case Enchant::Type::quick_charge: return "quick_charge";
			case Enchant::Type::soul_speed: return "soul_speed";
			default: return "unknown";
		}
	}

	BASEAPI static bool applyUnfilteredEnchant(ItemStackBase &out, EnchantmentInstance const& newEnchant, bool overwriteDuplicates);
	BASEAPI static bool removeEnchant(ItemStackBase &out, Enchant::Type typeToRemove);
	BASEAPI static void removeAllEnchants(ItemStackBase &out);

	MCAPI static int32_t const PROTECTIONFACTOR_SECONDARYCAP;
};

class EnchantmentInstance {
public:
	Enchant::Type mEnchantType;
	int32_t mLevel;

	EnchantmentInstance() : mEnchantType(Enchant::Type::invalid_enchantment), mLevel(0) {}
	EnchantmentInstance(Enchant::Type type, int32_t lvl) : mEnchantType(type), mLevel(lvl) {}

	inline std::string getName() const { return EnchantUtils::getEnchantName(this->mEnchantType); }
	inline std::string toString() const { return EnchantUtils::getEnchantNameAndLevel(this->mEnchantType, this->mLevel); }
	inline bool operator==(EnchantmentInstance const& rhs) { return ((this->mEnchantType == rhs.mEnchantType) && (this->mLevel == rhs.mLevel)); }
	inline bool operator!=(EnchantmentInstance const& rhs) { return !(*this == rhs); }
};
static_assert(sizeof(EnchantmentInstance) == 0x8);

class ItemEnchants {
	MCAPI std::vector<ListTag> _toList() const;
	MCAPI void _fromList(std::vector<ListTag> const &);

public:
	Enchant::Slot mSlot; // int32_t
	std::vector<EnchantmentInstance> mItemEnchants[3];

	MCAPI std::vector<EnchantmentInstance> getAllEnchants() const;
	MCAPI std::vector<std::string> getEnchantNames() const;
	MCAPI bool addEnchant(EnchantmentInstance, bool);
	MCAPI EnchantResult canEnchant(EnchantmentInstance, bool);
	MCAPI void read(ReadOnlyBinaryStream &);
	MCAPI ItemEnchants& operator=(ItemEnchants &&);

	inline std::vector<ListTag> save() const { return _toList(); }
	inline void load(std::vector<ListTag> const &list) { return _fromList(list); }
};
static_assert(sizeof(ItemEnchants) == 0x50);