#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "NBT.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"
#include "../dll.h"

enum class DataItemType : int8_t {
	BYTE = 0x0,
	SHORT = 0x1,
	INT = 0x2,
	FLOAT = 0x3,
	STRING = 0x4,
	NBT = 0x5,
	POS = 0x6, // blockpos
	LONG = 0x7,
	VEC3 = 0x8,
	UNKNOWN = 0x9,
};

namespace DataTypeMap {

template <typename T> DataItemType typeFor;

template <> inline DataItemType typeFor<int8_t>      = DataItemType::BYTE;
template <> inline DataItemType typeFor<int16_t>     = DataItemType::SHORT;
template <> inline DataItemType typeFor<int32_t>     = DataItemType::INT;
template <> inline DataItemType typeFor<float>       = DataItemType::FLOAT;
template <> inline DataItemType typeFor<std::string> = DataItemType::STRING;
template <> inline DataItemType typeFor<CompoundTag> = DataItemType::NBT;
template <> inline DataItemType typeFor<BlockPos>    = DataItemType::POS;
template <> inline DataItemType typeFor<int64_t>     = DataItemType::LONG;
template <> inline DataItemType typeFor<Vec3>        = DataItemType::VEC3;

template <typename T> struct neqFor {
	static bool neq(T const &lhs, T const &rhs) { return lhs != rhs; }
};
template <typename T> struct copyFor {
	static void copy(T &lhs, T const &rhs) { lhs = rhs; }
};

} // namespace DataTypeMap

// https://github.com/pmmp/BedrockProtocol/blob/master/src/types/entity/EntityMetadataProperties.php
namespace ActorDataIDs {

inline constexpr uint16_t FLAGS = 0x0;
inline constexpr uint16_t STRUCTURAL_INTEGRITY = 0x1;
inline constexpr uint16_t VARIANT = 0x2;
inline constexpr uint16_t COLOR_INDEX = 0x3;
inline constexpr uint16_t NAMETAG = 0x4; // NAME
inline constexpr uint16_t OWNER = 0x5;
inline constexpr uint16_t TARGET = 0x6;
inline constexpr uint16_t AIR_SUPPLY = 0x7;
inline constexpr uint16_t EFFECT_COLOR = 0x8;
inline constexpr uint16_t EFFECT_AMBIENCE = 0x9;
inline constexpr uint16_t JUMP_DURATION = 0xA;
inline constexpr uint16_t HURT = 0xB;
inline constexpr uint16_t HURT_DIR = 0xC;
inline constexpr uint16_t BOAT_ROW_TIME_LEFT = 0xD; // ROW_TIME_LEFT
inline constexpr uint16_t BOAT_ROW_TIME_RIGHT = 0xE; // ROW_TIME_RIGHT
inline constexpr uint16_t EXPERIENCE_VALUE = 0xF; // VALUE
inline constexpr uint16_t DISPLAY_TILE_RUNTIME_ID = 0x10;
inline constexpr uint16_t MINECART_DISPLAY_OFFSET = 0x11; // DISPLAY_OFFSET
inline constexpr uint16_t MINECART_HAS_DISPLAY = 0x12; // CUSTOM_DISPLAY
inline constexpr uint16_t SWELL = 0x13;
inline constexpr uint16_t OLD_SWELL = 0x14;
inline constexpr uint16_t SWELL_DIR = 0x15;
inline constexpr uint16_t CHARGE_AMOUNT = 0x16;
inline constexpr uint16_t CARRY_BLOCK_RUNTIME_ID = 0x17;
inline constexpr uint16_t CLIENT_EVENT = 0x18;
inline constexpr uint16_t USING_ITEM = 0x19;
inline constexpr uint16_t PLAYER_FLAGS = 0x1A;
inline constexpr uint16_t PLAYER_INDEX = 0x1B;
inline constexpr uint16_t BED_POSITION = 0x1C;
inline constexpr uint16_t FIREBALL_X_POWER = 0x1D; // X_POWER
inline constexpr uint16_t FIREBALL_Y_POWER = 0x1E; // Y_POWER
inline constexpr uint16_t FIREBALL_Z_POWER = 0x1F; // Z_POWER
inline constexpr uint16_t AUX_POWER = 0x20;
inline constexpr uint16_t FISHX = 0x21;
inline constexpr uint16_t FISHZ = 0x22;
inline constexpr uint16_t FISHANGLE = 0x23;
inline constexpr uint16_t AUX_VALUE_DATA = 0x24;
inline constexpr uint16_t LEASH_HOLDER = 0x25;
inline constexpr uint16_t SCALE = 0x26;
inline constexpr uint16_t HAS_NPC = 0x27;
inline constexpr uint16_t NPC_DATA = 0x28;
inline constexpr uint16_t ACTIONS = 0x29;
inline constexpr uint16_t AIR_SUPPLY_MAX = 0x2A;
inline constexpr uint16_t MARK_VARIANT = 0x2B;
inline constexpr uint16_t CONTAINER_TYPE = 0x2C;
inline constexpr uint16_t CONTAINER_SIZE = 0x2D;
inline constexpr uint16_t CONTAINER_STRENGTH_MODIFIER = 0x2E;
inline constexpr uint16_t BLOCK_TARGET = 0x2F;
inline constexpr uint16_t INV = 0x30;
inline constexpr uint16_t WITHER_TARGET_A = 0x31; // TARGET_A
inline constexpr uint16_t WITHER_TARGET_B = 0x32; // TARGET_B
inline constexpr uint16_t WITHER_TARGET_C = 0x33; // TARGET_C
inline constexpr uint16_t AERIAL_ATTACK = 0x34;
inline constexpr uint16_t BOUNDING_BOX_WIDTH = 0x35; // WIDTH
inline constexpr uint16_t BOUNDING_BOX_HEIGHT = 0x36; // HEIGHT
inline constexpr uint16_t FUSE_TIME = 0x37;
inline constexpr uint16_t SEAT_OFFSET = 0x38;
inline constexpr uint16_t SEAT_LOCK_RIDER_ROTATION = 0x39;
inline constexpr uint16_t SEAT_LOCK_RIDER_ROTATION_DEGREES = 0x3A;
inline constexpr uint16_t SEAT_ROTATION_OFFSET = 0x3B;
inline constexpr uint16_t DATA_RADIUS = 0x3C;
inline constexpr uint16_t DATA_WAITING = 0x3D;
inline constexpr uint16_t DATA_PARTICLE = 0x3E;
inline constexpr uint16_t PEEK_ID = 0x3F;
inline constexpr uint16_t ATTACH_FACE = 0x40;
inline constexpr uint16_t ATTACHED = 0x41;
inline constexpr uint16_t ATTACH_POS = 0x42;
inline constexpr uint16_t TRADE_TARGET = 0x43;
inline constexpr uint16_t CAREER = 0x44;
inline constexpr uint16_t HAS_COMMAND_BLOCK = 0x45;
inline constexpr uint16_t COMMAND_NAME = 0x46;
inline constexpr uint16_t LAST_COMMAND_OUTPUT = 0x47;
inline constexpr uint16_t TRACK_COMMAND_OUTPUT = 0x48;
inline constexpr uint16_t CONTROLLING_SEAT_INDEX = 0x49;
inline constexpr uint16_t STRENGTH = 0x4A;
inline constexpr uint16_t STRENGTH_MAX = 0x4B;
inline constexpr uint16_t DATA_SPELL_CASTING_COLOR = 0x4C;
inline constexpr uint16_t DATA_LIFETIME_TICKS = 0x4D;
inline constexpr uint16_t POSE_INDEX = 0x4E;
inline constexpr uint16_t DATA_TICK_OFFSET = 0x4F;
inline constexpr uint16_t NAMETAG_ALWAYS_SHOW = 0x50;
inline constexpr uint16_t COLOR_2_INDEX = 0x51;
inline constexpr uint16_t NAME_AUTHOR = 0x52;
inline constexpr uint16_t SCORE = 0x53;
inline constexpr uint16_t BALLOON_ANCHOR = 0x54;
inline constexpr uint16_t PUFFED_STATE = 0x55;
inline constexpr uint16_t BUBBLE_TIME = 0x56;
inline constexpr uint16_t AGENT = 0x57;
inline constexpr uint16_t SITTING_AMOUNT = 0x58;
inline constexpr uint16_t SITTING_AMOUNT_PREVIOUS = 0x59;
inline constexpr uint16_t EATING_COUNTER = 0x5A;
inline constexpr uint16_t FLAGS2 = 0x5B;
inline constexpr uint16_t LAYING_AMOUNT = 0x5C;
inline constexpr uint16_t LAYING_AMOUNT_PREVIOUS = 0x5D;
inline constexpr uint16_t DATA_DURATION = 0x5E;
inline constexpr uint16_t DATA_SPAWN_TIME = 0x5F;
inline constexpr uint16_t DATA_CHANGE_RATE = 0x60;
inline constexpr uint16_t DATA_CHANGE_ON_PICKUP = 0x61;
inline constexpr uint16_t DATA_PICKUP_COUNT = 0x62;
inline constexpr uint16_t INTERACT_TEXT = 0x63;
inline constexpr uint16_t TRADE_TIER = 0x64;
inline constexpr uint16_t MAX_TRADE_TIER = 0x65;
inline constexpr uint16_t TRADE_EXPERIENCE = 0x66;
inline constexpr uint16_t SKIN_ID = 0x67;
inline constexpr uint16_t SPAWNING_FRAMES = 0x68;
inline constexpr uint16_t COMMAND_BLOCK_TICK_DELAY = 0x69;
inline constexpr uint16_t COMMAND_BLOCK_EXECUTE_ON_FIRST_TICK = 0x6A;
inline constexpr uint16_t AMBIENT_SOUND_INTERVAL = 0x6B;
inline constexpr uint16_t AMBIENT_SOUND_INTERVAL_RANGE = 0x6C;
inline constexpr uint16_t AMBIENT_SOUND_EVENT_NAME = 0x6D;
inline constexpr uint16_t FALL_DAMAGE_MULTIPLIER = 0x6E;
inline constexpr uint16_t NAME_RAW_TEXT = 0x6F;
inline constexpr uint16_t CAN_RIDE_TARGET = 0x70;
inline constexpr uint16_t LOW_TIER_CURED_TRADE_DISCOUNT = 0x71;
inline constexpr uint16_t HIGH_TIER_CURED_TRADE_DISCOUNT = 0x72;
inline constexpr uint16_t NEARBY_CURED_TRADE_DISCOUNT = 0x73;
inline constexpr uint16_t NEARBY_CURED_DISCOUNT_TIME_STAMP = 0x74;
inline constexpr uint16_t HITBOX = 0x75;
inline constexpr uint16_t IS_BUOYANT = 0x76;
inline constexpr uint16_t BUOYANCY_DATA = 0x77;

} // namespace ActorDataIDs

class DataItem {
public:
	DataItemType type;
	uint16_t id;
	bool dirty;

	DataItem(DataItemType type, uint16_t id, bool dirty) : type(type), id(id), dirty(dirty) {}

	virtual ~DataItem() {}
	virtual MCAPI bool isDataEqual(DataItem const &rhs) const;
	virtual std::unique_ptr<DataItem> clone() const = 0;

	inline void setDirty() { dirty = true; }
	inline uint16_t getId() const { return id; }
};

template <typename T> class DataItem2 : public DataItem {
public:
	T value;
	DataItem2(uint16_t id, T const &value) : DataItem(DataTypeMap::typeFor<T>, id, true), value(value) {}
	MCAPI std::unique_ptr<DataItem> clone() const override;
};

template <> class DataItem2<int8_t> : public DataItem {
public:
	int8_t value;
	DataItem2(uint16_t id, int8_t const &value) : DataItem(DataTypeMap::typeFor<int8_t>, id, true), value(value) {}
	MCAPI std::unique_ptr<DataItem> clone() const override;

	inline bool getFlag(int32_t bit) const { return (1 << bit) & value; }
	inline void setFlag(int32_t bit) { value |= 1 << bit; }
	inline void clearFlag(int32_t bit) { value &= ~(1 << bit); }
};

template <> class DataItem2<int64_t> : public DataItem {
public:
	int64_t value;
	DataItem2(uint16_t id, int64_t const &value) : DataItem(DataTypeMap::typeFor<int64_t>, id, true), value(value) {}
	MCAPI std::unique_ptr<DataItem> clone() const override;

	inline bool getFlag(int32_t bit) const { return (1LL << bit) & value; }
	inline void setFlag(int32_t bit) { value |= 1LL << bit; }
	inline void clearFlag(int32_t bit) { value &= ~(1LL << bit); }
};