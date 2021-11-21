#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

enum class ActorEvent {
  NONE = 0x0,
  JUMP = 0x1,
  HURT = 0x2,
  DEATH = 0x3,
  START_ATTACKING = 0x4,
  STOP_ATTACKING = 0x5,
  TAMING_FAILED = 0x6,
  TAMING_SUCCEEDED = 0x7,
  SHAKE_WETNESS = 0x8,
  EAT_GRASS = 0xA,
  FISHHOOK_BUBBLE = 0xB,
  FISHHOOK_FISHPOS = 0xC,
  FISHHOOK_HOOKTIME = 0xD,
  FISHHOOK_TEASE = 0xE,
  SQUID_FLEEING = 0xF,
  ZOMBIE_CONVERTING = 0x10,
  PLAY_AMBIENT = 0x11,
  SPAWN_ALIVE = 0x12,
  START_OFFER_FLOWER = 0x13,
  STOP_OFFER_FLOWER = 0x14,
  LOVE_HEARTS = 0x15,
  VILLAGER_ANGRY = 0x16,
  VILLAGER_HAPPY = 0x17,
  WITCH_HAT_MAGIC = 0x18,
  FIREWORKS_EXPLODE = 0x19,
  IN_LOVE_HEARTS = 0x1A,
  SILVERFISH_MERGE_ANIM = 0x1B,
  GUARDIAN_ATTACK_SOUND = 0x1C,
  DRINK_POTION = 0x1D,
  THROW_POTION = 0x1E,
  PRIME_TNTCART = 0x1F,
  PRIME_CREEPER = 0x20,
  AIR_SUPPLY = 0x21,
  ADD_PLAYER_LEVELS = 0x22,
  GUARDIAN_MINING_FATIGUE = 0x23,
  AGENT_SWING_ARM = 0x24,
  DRAGON_START_DEATH_ANIM = 0x25,
  GROUND_DUST = 0x26,SHAKE = 0x27,
  FEED = 0x39,BABY_EAT = 0x3C,
  INSTANT_DEATH = 0x3D,
  NOTIFY_TRADE = 0x3E,
  LEASH_DESTROYED = 0x3F,
  CARAVAN_UPDATED = 0x40,
  TALISMAN_ACTIVATE = 0x41,
  UPDATE_STRUCTURE_FEATURE = 0x42,
  PLAYER_SPAWNED_MOB = 0x43,
  PUKE = 0x44,
  UPDATE_STACK_SIZE = 0x45,
  START_SWIMMING = 0x46,
  BALLOON_POP = 0x47,
  TREASURE_HUNT = 0x48,
  SUMMON_AGENT = 0x49,
  FINISHED_CHARGING_CROSSBOW = 0x4A,
  LANDED_ON_GROUND = 0x4B,
};

class ActorEventPacket : public Packet {
public:
  ActorRuntimeID mRuntimeId;
  ActorEvent mEventId;
  int mData; // idk what this is for

  inline ~ActorEventPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};