#pragma once

#include <functional>
#include <string>

#include <modutils.h>

#include "../Core/AutomaticID.h"
#include "LevelDataWrapper.h"
#include "../dll.h"

class Player;
class Dimension;
class PacketSender;
enum class Difficulty;
enum class GameType;
enum class BossEventUpdateType;
enum class ActorEvent : int8_t;
enum class MaterialType;

enum class LevelEvent {
	Undefined                     = 0x0,
	SoundClick                    = 0x3E8,
	SoundClickFail                = 0x3E9,
	SoundLaunch                   = 0x3EA,
	SoundOpenDoor                 = 0x3EB,
	SoundFizz                     = 0x3EC,
	SoundFuse                     = 0x3ED,
	SoundPlayRecording            = 0x3EE,
	SoundGhastWarning             = 0x3EF,
	SoundGhastFireball            = 0x3F0,
	SoundBlazeFireball            = 0x3F1,
	SoundZombieWoodenDoor         = 0x3F2,
	SoundZombieDoorCrash          = 0x3F4,
	SoundZombieInfected           = 0x3F8,
	SoundZombieConverted          = 0x3F9,
	SoundEndermanTeleport         = 0x3FA,
	SoundAnvilBroken              = 0x3FC,
	SoundAnvilUsed                = 0x3FD,
	SoundAnvilLand                = 0x3FE,
	SoundInfinityArrowPickup      = 0x406,
	SoundTeleportEnderPearl       = 0x408,
	SoundAddItem                  = 0x410,
	SoundItemFrameBreak           = 0x411,
	SoundItemFramePlace           = 0x412,
	SoundItemFrameRemoveItem      = 0x413,
	SoundItemFrameRotateItem      = 0x414,
	SoundExperienceOrbPickup      = 0x41B,
	SoundTotemUsed                = 0x41C,
	SoundArmorStandBreak          = 0x424,
	SoundArmorStandHit            = 0x425,
	SoundArmorStandLand           = 0x426,
	SoundArmorStandPlace          = 0x427,
	ParticlesShoot                = 0x7D0,
	ParticlesDestroyBlock         = 0x7D1,
	ParticlesPotionSplash         = 0x7D2,
	ParticlesEyeOfEnderDeath      = 0x7D3,
	ParticlesMobBlockSpawn        = 0x7D4,
	ParticleCropGrowth            = 0x7D5,
	ParticleSoundGuardianGhost    = 0x7D6,
	ParticleDeathSmoke            = 0x7D7,
	ParticleDenyBlock             = 0x7D8,
	ParticleGenericSpawn          = 0x7D9,
	ParticlesDragonEgg            = 0x7DA,
	ParticlesCropEaten            = 0x7DB,
	ParticlesCrit                 = 0x7DC,
	ParticlesTeleport             = 0x7DD,
	ParticlesCrackBlock           = 0x7DE,
	ParticlesBubble               = 0x7DF,
	ParticlesEvaporate            = 0x7E0,
	ParticlesDestroyArmorStand    = 0x7E1,
	ParticlesBreakingEgg          = 0x7E2,
	ParticleDestroyEgg            = 0x7E3,
	ParticlesEvaporateWater       = 0x7E4,
	ParticlesDestroyBlockNoSound  = 0x7E5,
	ParticlesKnockbackRoar        = 0x7E6,
	ParticlesTeleportTrail        = 0x7E7,
	ParticlesPointCloud           = 0x7E8,
	ParticlesExplosion            = 0x7E9,
	ParticlesBlockExplosion       = 0x7EA,
	StartRaining                  = 0x0BB9,
	StartThunderstorm             = 0x0BBA,
	StopRaining                   = 0x0BBB,
	StopThunderstorm              = 0x0BBC,
	GlobalPause                   = 0x0BBD,
	SimTimeStep                   = 0x0BBE,
	SimTimeScale                  = 0x0BBF,
	ActivateBlock                 = 0x0DAC,
	CauldronExplode               = 0x0DAD,
	CauldronDyeArmor              = 0x0DAE,
	CauldronCleanArmor            = 0x0DAF,
	CauldronFillPotion            = 0x0DB0,
	CauldronTakePotion            = 0x0DB1,
	CauldronFillWater             = 0x0DB2,
	CauldronTakeWater             = 0x0DB3,
	CauldronAddDye                = 0x0DB4,
	CauldronCleanBanner           = 0x0DB5,
	CauldronFlush                 = 0x0DB6,
	AgentSpawnEffect              = 0x0DB7,
	CauldronFillLava              = 0x0DB8,
	CauldronTakeLava              = 0x0DB9,
	StartBlockCracking            = 0x0E10,
	StopBlockCracking             = 0x0E11,
	UpdateBlockCracking           = 0x0E12,
	AllPlayersSleeping            = 0x2648,
	JumpPrevented                 = 0x2652,
	ParticleLegacyEvent           = 0x4000
};

enum class LevelSoundEvent {
	ItemUseOn                      = 0x0,
	Hit                            = 0x1,
	Step                           = 0x2,
	Fly                            = 0x3,
	Jump                           = 0x4,
	Break                          = 0x5,
	Place                          = 0x6,
	HeavyStep                      = 0x7,
	Gallop                         = 0x8,
	Fall                           = 0x9,
	Ambient                        = 0x0A,
	AmbientBaby                    = 0x0B,
	AmbientInWater                 = 0x0C,
	Breathe                        = 0x0D,
	Death                          = 0x0E,
	DeathInWater                   = 0x0F,
	DeathToZombie                  = 0x10,
	Hurt                           = 0x11,
	HurtInWater                    = 0x12,
	Mad                            = 0x13,
	Boost                          = 0x14,
	Bow                            = 0x15,
	SquishBig                      = 0x16,
	SquishSmall                    = 0x17,
	FallBig                        = 0x18,
	FallSmall                      = 0x19,
	Splash                         = 0x1A,
	Fizz                           = 0x1B,
	Flap                           = 0x1C,
	Swim                           = 0x1D,
	Drink                          = 0x1E,
	Eat                            = 0x1F,
	Takeoff                        = 0x20,
	Shake                          = 0x21,
	Plop                           = 0x22,
	Land                           = 0x23,
	Saddle                         = 0x24,
	Armor                          = 0x25,
	ArmorPlace                     = 0x26,
	AddChest                       = 0x27,
	Throw                          = 0x28,
	Attack                         = 0x29,
	AttackNoDamage                 = 0x2A,
	AttackStrong                   = 0x2B,
	Warn                           = 0x2C,
	Shear                          = 0x2D,
	Milk                           = 0x2E,
	Thunder                        = 0x2F,
	Explode                        = 0x30,
	Fire                           = 0x31,
	Ignite                         = 0x32,
	Fuse                           = 0x33,
	Stare                          = 0x34,
	Spawn                          = 0x35,
	Shoot                          = 0x36,
	BreakBlock                     = 0x37,
	Launch                         = 0x38,
	Blast                          = 0x39,
	LargeBlast                     = 0x3A,
	Twinkle                        = 0x3B,
	Remedy                         = 0x3C,
	Unfect                         = 0x3D,
	LevelUp                        = 0x3E,
	BowHit                         = 0x3F,
	BulletHit                      = 0x40,
	ExtinguishFire                 = 0x41,
	ItemFizz                       = 0x42,
	ChestOpen                      = 0x43,
	ChestClosed                    = 0x44,
	ShulkerBoxOpen                 = 0x45,
	ShulkerBoxClosed               = 0x46,
	EnderChestOpen                 = 0x47,
	EnderChestClosed               = 0x48,
	PowerOn                        = 0x49,
	PowerOff                       = 0x4A,
	Attach                         = 0x4B,
	Detach                         = 0x4C,
	Deny                           = 0x4D,
	Tripod                         = 0x4E,
	Pop                            = 0x4F,
	DropSlot                       = 0x50,
	Note                           = 0x51,
	Thorns                         = 0x52,
	PistonIn                       = 0x53,
	PistonOut                      = 0x54,
	Portal                         = 0x55,
	Water                          = 0x56,
	LavaPop                        = 0x57,
	Lava                           = 0x58,
	Burp                           = 0x59,
	BucketFillWater                = 0x5A,
	BucketFillLava                 = 0x5B,
	BucketEmptyWater               = 0x5C,
	BucketEmptyLava                = 0x5D,
	EquipChain                     = 0x5E,
	EquipDiamond                   = 0x5F,
	EquipGeneric                   = 0x60,
	EquipGold                      = 0x61,
	EquipIron                      = 0x62,
	EquipLeather                   = 0x63,
	EquipElytra                    = 0x64,
	Record13                       = 0x65,
	RecordCat                      = 0x66,
	RecordBlocks                   = 0x67,
	RecordChirp                    = 0x68,
	RecordFar                      = 0x69,
	RecordMall                     = 0x6A,
	RecordMellohi                  = 0x6B,
	RecordStal                     = 0x6C,
	RecordStrad                    = 0x6D,
	RecordWard                     = 0x6E,
	Record11                       = 0x6F,
	RecordWait                     = 0x70,
	RecordNull                     = 0x71,
	Flop                           = 0x72,
	GuardianCurse                  = 0x73,
	MobWarning                     = 0x74,
	MobWarningBaby                 = 0x75,
	Teleport                       = 0x76,
	ShulkerOpen                    = 0x77,
	ShulkerClose                   = 0x78,
	Haggle                         = 0x79,
	HaggleYes                      = 0x7A,
	HaggleNo                       = 0x7B,
	HaggleIdle                     = 0x7C,
	ChorusGrow                     = 0x7D,
	ChorusDeath                    = 0x7E,
	Glass                          = 0x7F,
	PotionBrewed                   = 0x80,
	CastSpell                      = 0x81,
	PrepareAttackSpell             = 0x82,
	PrepareSummon                  = 0x83,
	PrepareWololo                  = 0x84,
	Fang                           = 0x85,
	Charge                         = 0x86,
	TakePicture                    = 0x87,
	PlaceLeashKnot                 = 0x88,
	BreakLeashKnot                 = 0x89,
	AmbientGrowl                   = 0x8A,
	AmbientWhine                   = 0x8B,
	AmbientPant                    = 0x8C,
	AmbientPurr                    = 0x8D,
	AmbientPurreow                 = 0x8E,
	DeathMinVolume                 = 0x8F,
	DeathMidVolume                 = 0x90,
	ImitateBlaze                   = 0x91,
	ImitateCaveSpider              = 0x92,
	ImitateCreeper                 = 0x93,
	ImitateElderGuardian           = 0x94,
	ImitateEnderDragon             = 0x95,
	ImitateEnderman                = 0x96,
	ImitateEndermite               = 0x97,
	ImitateEvocationIllager        = 0x98,
	ImitateGhast                   = 0x99,
	ImitateHusk                    = 0x9A,
	ImitateIllusionIllager         = 0x9B,
	ImitateMagmaCube               = 0x9C,
	ImitatePolarBear               = 0x9D,
	ImitateShulker                 = 0x9E,
	ImitateSilverfish              = 0x9F,
	ImitateSkeleton                = 0x0A0,
	ImitateSlime                   = 0x0A1,
	ImitateSpider                  = 0x0A2,
	ImitateStray                   = 0x0A3,
	ImitateVex                     = 0x0A4,
	ImitateVindicationIllager      = 0x0A5,
	ImitateWitch                   = 0x0A6,
	ImitateWither                  = 0x0A7,
	ImitateWitherSkeleton          = 0x0A8,
	ImitateWolf                    = 0x0A9,
	ImitateZombie                  = 0x0AA,
	ImitateZombiePigman            = 0x0AB,
	ImitateZombieVillager          = 0x0AC,
	EnderEyePlaced                 = 0x0AD,
	EndPortalCreated               = 0x0AE,
	AnvilUse                       = 0x0AF,
	BottleDragonBreath             = 0x0B0,
	PortalTravel                   = 0x0B1,
	TridentHit                     = 0x0B2,
	TridentReturn                  = 0x0B3,
	TridentRiptide_1               = 0x0B4,
	TridentRiptide_2               = 0x0B5,
	TridentRiptide_3               = 0x0B6,
	TridentThrow                   = 0x0B7,
	TridentThunder                 = 0x0B8,
	TridentHitGround               = 0x0B9,
	Default                        = 0x0BA,
	FletchingTableUse              = 0x0BB,
	ElemConstructOpen              = 0x0BC,
	IceBombHit                     = 0x0BD,
	BalloonPop                     = 0x0BE,
	LTReactionIceBomb              = 0x0BF,
	LTReactionBleach               = 0x0C0,
	LTReactionElephantToothpaste   = 0x0C1,
	LTReactionElephantToothpaste2  = 0x0C2,
	LTReactionGlowStick            = 0x0C3,
	LTReactionGlowStick2           = 0x0C4,
	LTReactionLuminol              = 0x0C5,
	LTReactionSalt                 = 0x0C6,
	LTReactionFertilizer           = 0x0C7,
	LTReactionFireball             = 0x0C8,
	LTReactionMagnesiumSalt        = 0x0C9,
	LTReactionMiscFire             = 0x0CA,
	LTReactionFire                 = 0x0CB,
	LTReactionMiscExplosion        = 0x0CC,
	LTReactionMiscMystical         = 0x0CD,
	LTReactionMiscMystical2        = 0x0CE,
	LTReactionProduct              = 0x0CF,
	SparklerUse                    = 0x0D0,
	GlowStickUse                   = 0x0D1,
	SparklerActive                 = 0x0D2,
	ConvertToDrowned               = 0x0D3,
	BucketFillFish                 = 0x0D4,
	BucketEmptyFish                = 0x0D5,
	BubbleColumnUpwards            = 0x0D6,
	BubbleColumnDownwards          = 0x0D7,
	BubblePop                      = 0x0D8,
	BubbleUpInside                 = 0x0D9,
	BubbleDownInside               = 0x0DA,
	HurtBaby                       = 0x0DB,
	DeathBaby                      = 0x0DC,
	StepBaby                       = 0x0DD,
	SpawnBaby                      = 0x0DE,
	Born                           = 0x0DF,
	TurtleEggBreak                 = 0x0E0,
	TurtleEggCrack                 = 0x0E1,
	TurtleEggHatched               = 0x0E2,
	LayEgg                         = 0x0E3,
	TurtleEggAttacked              = 0x0E4,
	BeaconActivate                 = 0x0E5,
	BeaconAmbient                  = 0x0E6,
	BeaconDeactivate               = 0x0E7,
	BeaconPower                    = 0x0E8,
	ConduitActivate                = 0x0E9,
	ConduitAmbient                 = 0x0EA,
	ConduitAttack                  = 0x0EB,
	ConduitDeactivate              = 0x0EC,
	ConduitShort                   = 0x0ED,
	Swoop                          = 0x0EE,
	BambooSaplingPlace             = 0x0EF,
	PreSneeze                      = 0x0F0,
	Sneeze                         = 0x0F1,
	AmbientTame                    = 0x0F2,
	Scared                         = 0x0F3,
	ScaffoldingClimb               = 0x0F4,
	CrossbowLoadingStart           = 0x0F5,
	CrossbowLoadingMiddle          = 0x0F6,
	CrossbowLoadingEnd             = 0x0F7,
	CrossbowShoot                  = 0x0F8,
	CrossbowQuickChargeStart       = 0x0F9,
	CrossbowQuickChargeMiddle      = 0x0FA,
	CrossbowQuickChargeEnd         = 0x0FB,
	AmbientAggressive              = 0x0FC,
	AmbientWorried                 = 0x0FD,
	CantBreed                      = 0x0FE,
	ShieldBlock                    = 0x0FF,
	LecternBookPlace               = 0x100,
	GrindstoneUse                  = 0x101,
	Bell                           = 0x102,
	CampfireCrackle                = 0x103,
	Roar                           = 0x104,
	Stun                           = 0x105,
	SweetBerryBushHurt             = 0x106,
	SweetBerryBushPick             = 0x107,
	CartographyTableUse            = 0x108,
	StonecutterUse                 = 0x109,
	ComposterEmpty                 = 0x10A,
	ComposterFill                  = 0x10B,
	ComposterFillLayer             = 0x10C,
	ComposterReady                 = 0x10D,
	BarrelOpen                     = 0x10E,
	BarrelClose                    = 0x10F,
	RaidHorn                       = 0x110,
	LoomUse                        = 0x111,
	AmbientInRaid                  = 0x112,
	UICartographyTableUse          = 0x113,
	UIStonecutterUse               = 0x114,
	UILoomUse                      = 0x115,
	SmokerUse                      = 0x116,
	BlastFurnaceUse                = 0x117,
	SmithingTableUse               = 0x118,
	Screech                        = 0x119,
	Sleep                          = 0x11A,
	FurnaceUse                     = 0x11B,
	MooshroomConvert               = 0x11C,
	MilkSuspiciously               = 0x11D,
	Celebrate                      = 0x11E,
	JumpPrevent                    = 0x11F,
	AmbientPollinate               = 0x120,
	BeehiveDrip                    = 0x121,
	BeehiveEnter                   = 0x122,
	BeehiveExit                    = 0x123,
	BeehiveWork                    = 0x124,
	BeehiveShear                   = 0x125,
	HoneybottleDrink               = 0x126,
	AmbientCave                    = 0x127,
	Retreat                        = 0x128,
	ConvertToZombified             = 0x129,
	Admire                         = 0x12A,
	StepLava                       = 0x12B,
	Tempt                          = 0x12C,
	Panic                          = 0x12D,
	Angry                          = 0x12E,
	AmbientMoodWarpedForest        = 0x12F,
	AmbientMoodSoulsandValley      = 0x130,
	AmbientMoodNetherWastes        = 0x131,
	AmbientMoodBasaltDeltas        = 0x132,
	AmbientMoodCrimsonForest       = 0x133,
	RespawnAnchorCharge            = 0x134,
	RespawnAnchorDeplete           = 0x135,
	RespawnAnchorSetSpawn          = 0x136,
	RespawnAnchorAmbient           = 0x137,
	SoulEscapeQuiet                = 0x138,
	SoulEscapeLoud                 = 0x139,
	RecordPigstep                  = 0x13A,
	LinkCompassToLodestone         = 0x13B,
	UseSmithingTable               = 0x13C,
	EquipNetherite                 = 0x13D,
	AmbientLoopWarpedForest        = 0x13E,
	AmbientLoopSoulsandValley      = 0x13F,
	AmbientLoopNetherWastes        = 0x140,
	AmbientLoopBasaltDeltas        = 0x141,
	AmbientLoopCrimsonForest       = 0x142,
	AmbientAdditionWarpedForest    = 0x143,
	AmbientAdditionSoulsandValley  = 0x144,
	AmbientAdditionNetherWastes    = 0x145,
	AmbientAdditionBasaltDeltas    = 0x146,
	AmbientAdditionCrimsonForest   = 0x147
};

enum class ParticleType {
	Undefined              = 0,
	Bubble                 = 1,
	BubbleManual           = 2,
	Crit                   = 3,
	BlockForceField        = 4,
	Smoke                  = 5,
	Explode                = 6,
	Evaporation            = 7,
	Flame                  = 8,
	CandleFlame            = 9,
	Lava                   = 10,
	LargeSmoke             = 11,
	RedDust                = 12,
	RisingBorderDust       = 13,
	IconCrack              = 14,
	SnowballPoof           = 15,
	LargeExplode           = 16,
	HugeExplosion          = 17,
	MobFlame               = 18,
	Heart                  = 19,
	Terrain                = 20,
	TownAura               = 21,
	Portal                 = 22,
	MobPortal              = 23,
	WaterSplash            = 24,
	WaterSplashManual      = 25,
	WaterWake              = 26,
	DripWater              = 27,
	DripLava               = 28,
	DripHoney              = 29,
	StalactiteDripWater    = 30,
	StalactiteDripLava     = 31,
	FallingDust            = 32,
	MobSpell               = 33,
	MobSpellAmbient        = 34,
	MobSpellInstantaneous  = 35,
	Ink                    = 36,
	Slime                  = 37,
	RainSplash             = 38,
	VillagerAngry          = 39,
	VillagerHappy          = 40,
	EnchantingTable        = 41,
	TrackingEmitter        = 42,
	Note                   = 43,
	WitchSpell             = 44,
	CarrotBoost            = 45,
	MobAppearance          = 46,
	EndRod                 = 47,
	DragonBreath           = 48,
	Spit                   = 49,
	Totem                  = 50,
	Food                   = 51,
	FireworksStarter       = 52,
	Fireworks              = 53,
	FireworksOverlay       = 54,
	BalloonGas             = 55,
	ColoredFlame           = 56,
	Sparkler               = 57,
	Conduit                = 58,
	BubbleColumnUp         = 59,
	BubbleColumnDown       = 60,
	Sneeze                 = 61,
	ShulkerBullet          = 62,
	Bleach                 = 63,
	DragonDestroyBlock     = 64,
	MyceliumDust           = 65,
	FallingBorderDust      = 66,
	CampfireSmoke          = 67,
	CampfireSmokeTall      = 68,
	DragonBreathFire       = 69,
	DragonBreathTrail      = 70,
	BlueFlame              = 71,
	Soul                   = 72,
	ObsidianTear           = 73,
	PortalReverse          = 74
};

class Level {
public:
	MCAPI void save(void);
	MCAPI void saveGameData(void);
	MCAPI void saveVillages(void);
	MCAPI void saveBiomeData(void);
	MCAPI void saveLevelData(void);
	MCAPI void saveDirtyChunks(void);

	MCAPI int getNewPlayerId(void) const;
	MCAPI class GameRules &getGameRules(void);
	MCAPI class Player *getRandomPlayer(void);
	MCAPI enum Difficulty getDifficulty(void) const;
	MCAPI class Player *getPrimaryLocalPlayer(void) const;
	MCAPI class Color getPlayerColor(class Player const &) const;
	MCAPI struct AdventureSettings &getAdventureSettings(void);
	MCAPI class Actor *getRuntimeEntity(class ActorRuntimeID, bool) const;
	MCAPI class ITickingArea *getTickingArea(class mce::UUID const &) const;
	MCAPI float getSpecialMultiplier(AutomaticID<class Dimension, int>);
	MCAPI class MapItemSavedData *getMapSavedData(struct ActorUniqueID);
	MCAPI class Dimension *getDimension(class AutomaticID<class Dimension, int>) const;

	// slow func, has to iterate through whole player list and match mce::UUID
	// EZ player database is probably a lot faster
	MCAPI std::string const &getPlayerXUID(class mce::UUID const &) const;
	
	MCAPI std::string const &getPlayerPlatformOnlineId(class mce::UUID const &) const;
	BASEAPI ActorUniqueID getNewUniqueID() const;
	BASEAPI PacketSender &getPacketSender() const;
	BASEAPI uint64_t getServerTick();
	BASEAPI LevelDataWrapper &getLevelDataWrapper();

	MCAPI void setDefaultGameType(enum GameType);

	MCAPI bool hasCommandsEnabled(void) const;
	MCAPI bool hasExperimentalGameplayEnabled(void) const;

	MCAPI void forEachPlayer(std::function<bool(Player &)>);
	MCAPI void forEachPlayer(std::function<bool(Player const &)>) const;
	MCAPI void forEachDimension(std::function<bool(Dimension const &)>);

	MCAPI void broadcastBossEvent(enum BossEventUpdateType);
	MCAPI void broadcastEntityEvent(class Actor *, enum ActorEvent, int);
	MCAPI void broadcastLevelEvent(enum LevelEvent, class Vec3 const &, int, class Player *);
	MCAPI void broadcastLevelEvent(enum LevelEvent, class CompoundTag const &, class Player *);
	MCAPI void broadcastDimensionEvent(class BlockSource &, enum LevelEvent, class Vec3 const &, int, class Player *);
	MCAPI void broadcastSoundEvent(
		class BlockSource &, enum LevelSoundEvent, class Vec3 const &, int, struct ActorDefinitionIdentifier const &, bool, bool);

	MCAPI void playSound(enum LevelSoundEvent, class Vec3 const &, int, struct ActorDefinitionIdentifier const &, bool, bool);
	MCAPI void playSound(
		class BlockSource &, enum LevelSoundEvent, class Vec3 const &, int, struct ActorDefinitionIdentifier const &, bool, bool);
	MCAPI void playSynchronizedSound(
		class BlockSource &, enum LevelSoundEvent, class Vec3 const &, int, struct ActorDefinitionIdentifier const &, bool, bool);

	MCAPI void tickEntities(void);
	MCAPI void updateWeather(float, int, float, int);
	MCAPI void denyEffect(class Vec3 const &);
	MCAPI void forceRemoveEntity(class Actor &);
	MCAPI void addListener(class LevelListener &);
	MCAPI bool isPlayerSuspended(class Player &) const;
	MCAPI void requestMapInfo(struct ActorUniqueID);
	MCAPI bool copyAndLockMap(struct ActorUniqueID, struct ActorUniqueID);
	MCAPI void onChunkDiscarded(class LevelChunk &);
	MCAPI void removeListener(class LevelListener &);
	MCAPI struct ActorUniqueID expandMapByID(struct ActorUniqueID, bool);
	MCAPI void potionSplash(class Vec3 const &, class Color const &, bool);
	MCAPI class Actor *fetchEntity(struct ActorUniqueID entityId, bool getRemoved) const;
	MCAPI void unregisterTemporaryPointer(class _TickPtr &);
	MCAPI bool destroyBlock(class BlockSource &, class BlockPos const &, bool);
	MCAPI bool extinguishFire(class BlockSource &, class BlockPos const &, unsigned char);
	MCAPI void explode(class BlockSource &, class Actor *, class Vec3 const &, float, bool, bool, float, bool);
	MCAPI class Dimension &createDimension(class AutomaticID<class Dimension, int>);
	MCAPI bool checkAndHandleMaterial(class AABB const &, enum MaterialType, class Actor *);
	MCAPI class Player *findPlayer(std::function<bool(Player const &)>) const;
	MCAPI void addTerrainParticleEffect(class BlockPos const &, class Block const &, class Vec3 const &, float, float, float);
	MCAPI void entityChangeDimension(class Actor &, class AutomaticID<class Dimension, int>);
	MCAPI class Particle * addParticle(enum ParticleType, class Vec3 const &, class Vec3 const &, int, class CompoundTag const *, bool);
	MCAPI class MapItemSavedData &createMapSavedData(struct ActorUniqueID const &,
		class BlockPos const &, class AutomaticID<class Dimension, int>, int);
	MCAPI void spawnParticleEffect(std::string const &, class Vec3 const &, class Dimension *);
	MCAPI void requestPlayerChangeDimension(class Player &, std::unique_ptr<class ChangeDimensionRequest>);
	 
	MCAPI Level(class SoundPlayer &, std::unique_ptr<class LevelStorage>, class IMinecraftEventing &, bool, class Scheduler &,
			class StructureManager &, class ResourcePackManager &, class IEntityRegistryOwner &,
			std::unique_ptr<class BlockComponentFactory>, std::unique_ptr<class BlockDefinitionGroup>);
	
	BUILD_ACCESS(class BlockPalette *, GlobalBlockPalette, 1856);

	BUILD_ACCESS_MUT(ActorUniqueID, mLastUniqueID, 0x1A0);
	BUILD_ACCESS_MUT(std::vector<class Player *>, mActivePlayers, 0x58); // Level::forEachPlayer
	BUILD_ACCESS_MUT(std::unique_ptr<class Spawner>, mMobSpawner, 0x7B0); // enderPearlItem::use
	BUILD_ACCESS_MUT(std::unique_ptr<class ActorEventCoordinator>, mActorEventCoordinator, 0x1F68); // Player::attack
	BUILD_ACCESS_MUT(class ActorFactory, mActorFactory, 0x2068); // _anonymous_namespace_::_spawnEntityAt, xref: CommandUtils::spawnEntityAt
	BUILD_ACCESS_MUT(bool, mServerAuthoritativeMovement, 0x2508); // ServerNetworkHandler::_sendLevelData - 0x2090 - 0x28
};