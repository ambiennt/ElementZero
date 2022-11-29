#include "pch.h"

#include "global.h"

#include <Level/LevelData.h>

class HomeCommand : public Command {
public:
  void execute(CommandOrigin const &origin, CommandOutput &output) {

    if (origin.getOriginType() != CommandOriginType::Player) {
      output.error("commands.generic.error.invalidPlayer", {"/home"});
      return;
    }

    auto& source = *reinterpret_cast<Player*>(origin.getEntity());
    const auto& spawnPos = source.mPlayerRespawnPoint.mSpawnBlockPos;

    if (spawnPos.y < 0) {
      output.error("commands.home.error");
      return;
    }

    source.teleport(
        {(float)spawnPos.x, (float)spawnPos.y, (float)spawnPos.z}, Vec3::ZERO, 0);
    output.success("commands.home.success");
  }

  static void setup(CommandRegistry *registry) {
    registry->registerCommand(
        "home", "commands.home.description", CommandPermissionLevel::Any, CommandFlagCheat, CommandFlagNone);
    registry->registerOverload<HomeCommand>("home");
  }
};

class SpawnCommand : public Command {
public:
  void execute(CommandOrigin const &origin, CommandOutput &output) {

    if (origin.getOriginType() != CommandOriginType::Player) {
      output.error("commands.generic.error.invalidPlayer", {"/spawn"});
      return;
    }

    const auto &wrapper = LocateService<Level>()->mLevelDataWrapper;
    if (!wrapper->mHasSpawnPos) {
      output.error("commands.spawn.error.not.set");
      return;
    }

    auto& source = *reinterpret_cast<Player*>(origin.getEntity());
    auto spawnPos = wrapper->getSpawnPos();

    if (spawnPos.y > 256) {
      output.error("commands.spawn.error.not.set");
      return;
    }

    source.teleport(
        {(float)spawnPos.x, (float)spawnPos.y, (float)spawnPos.z}, Vec3::ZERO, 0);
    output.success("commands.spawn.success");
  }

  static void setup(CommandRegistry *registry) {
    registry->registerCommand(
        "spawn", "commands.spawn.description", CommandPermissionLevel::Any, CommandFlagCheat, CommandFlagNone);
    registry->registerOverload<SpawnCommand>("spawn");
  }
};

void registerHome(CommandRegistry *registry) {
  HomeCommand::setup(registry);
  SpawnCommand::setup(registry);
}