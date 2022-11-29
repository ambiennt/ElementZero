#pragma once

#include <string>

#include "BlockSourceListener.h"

namespace cg {
	class ImageBuffer;
}

enum class ParticleType;
enum class LevelEvent : int16_t;
enum class LevelSoundEvent;

class HashedString;
class Vec3;
class BlockPos;
class CompoundTag;
class MolangVariableMap;
class LevelChunk;
class ChunkSource;
class ScreenshotOptions;

struct TextureUVCoordinateSet;
struct ActorDefinitionIdentifier;

class LevelListener : public BlockSourceListener {
public:
	virtual void allChanged();
	virtual void addParticle(ParticleType, Vec3 const &, Vec3 const &, int32_t, CompoundTag const *, bool);
	virtual void sendServerLegacyParticle(ParticleType, Vec3 const &, Vec3 const &, int32_t);
	virtual void addParticleEffect(HashedString const &, Actor const &, HashedString const &, Vec3 const &, MolangVariableMap const &);
	virtual void addParticleEffect(HashedString const &, Vec3 const &, MolangVariableMap const &);
	virtual void addTerrainParticleEffect(BlockPos const &, Block const &, Vec3 const &, float, float, float);
	virtual void addTerrainSlideEffect(BlockPos const &, Block const &, Vec3 const &, float, float, float);
	virtual void addBreakingItemParticleEffect(Vec3 const &, ParticleType, TextureUVCoordinateSet const &, bool);
	virtual void playMusic(std::string const &, Vec3 const &, float, float);
	virtual void playStreamingMusic(std::string const &, int32_t, int32_t, int32_t);
	virtual void onEntityAdded(Actor &);
	virtual void onEntityRemoved(Actor &);
	virtual void onChunkLoaded(ChunkSource &, LevelChunk &);
	virtual void onChunkUnloaded(LevelChunk &);
	virtual void onLevelDestruction(std::string const &);
	virtual void levelEvent(enum class LevelEvent, CompoundTag const &);
	virtual void levelEvent(enum class LevelEvent, const Vec3 &pos, int32_t data); // this func only handles LevelEvent enum types: 0xBBB, 0xBB9, 0xBBA, 0xBBC
	virtual void levelSoundEvent(std::string const &, Vec3 const &, float, float);
	virtual void levelSoundEvent(LevelSoundEvent, Vec3 const &, int32_t, ActorDefinitionIdentifier const &, bool, bool);
	virtual void stopSoundEvent(std::string const &);
	virtual void stopAllSounds();
	virtual void takePicture(cg::ImageBuffer &, Actor *, Actor *, ScreenshotOptions &);
	virtual void playerListChanged();
};