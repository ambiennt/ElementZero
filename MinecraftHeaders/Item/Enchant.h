#pragma once

#include <string>
#include <vector>

#include "../Core/Util.h"
#include "../Core/NBT.h"
#include "../dll.h"

class ActorDamageSource;
class Actor;
class ItemInstance;
class EnchantUtils;
class EnchantmentInstance;

class Enchant {
public:
  enum class Type {
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
  enum struct Frequency {
    VeryRare         = 1,
    Rare             = 3,
    Uncommon         = 10,
    Common           = 30
  };

  enum struct Slot {
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

  Type type{};
  Frequency freq{};
  bool lootable{};
  Slot primarySlot{};
  Slot secondarySlot{};
  int compatibility{};
  std::string description;
  Util::HashString stringId;
  bool experimental{};
  bool disabled{};

  MCAPI virtual ~Enchant();
  MCAPI virtual bool isCompatibleWith(Type) const;
  MCAPI virtual int getMinCost(int) const;
  MCAPI virtual int getMaxCost(int) const;
  MCAPI virtual short getMinLevel(void) const;
  MCAPI virtual short getMaxLevel(void) const;
  MCAPI virtual int getDamageProtection(int, ActorDamageSource const &) const;
  MCAPI virtual float getDamageBonus(int, Actor const &) const;
  MCAPI virtual void doPostAttack(Actor &, Actor &, int) const;
  MCAPI virtual void doPostHurt(ItemInstance &, Actor &, Actor &, int) const;
  MCAPI virtual bool isMeleeDamageEnchant() const;
  MCAPI virtual bool isProtectionEnchant() const;
  MCAPI virtual bool isTreasureOnly() const;
};

class EnchantUtils {
public:
  MCAPI static std::string getEnchantNameAndLevel(Enchant::Type type, int);
  MCAPI static bool applyEnchant(class ItemStackBase&, EnchantmentInstance const&, bool); //bool - allow non vanilla enchants
  inline static char const *getEnchantName(Enchant::Type type) {
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
};

class EnchantmentInstance {
public:
  Enchant::Type type;
  int level;

  inline std::string getName() const { return EnchantUtils::getEnchantName(type); }

  inline std::string toString() const { return EnchantUtils::getEnchantNameAndLevel(type, level); }
};

class ItemEnchants {
public:
  Enchant::Slot slot;
  std::vector<EnchantmentInstance> list[3];

  MCAPI std::vector<EnchantmentInstance> getAllEnchants() const;
  MCAPI std::vector<std::string> getEnchantNames() const;

private:
  MCAPI std::vector<ListTag> _toList() const;
  MCAPI void _fromList(std::vector<ListTag> const &);

public:
  inline std::vector<ListTag> save() const { return _toList(); }
  inline void load(std::vector<ListTag> const &list) { return _fromList(list); }
};