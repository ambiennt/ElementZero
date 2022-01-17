#pragma once

#include <yaml.h>
#include <functional>
#include <Core/Core.h>
#include <Core/FeatureOptionID.h>
#include <hook.h>
#include <base/log.h>
#include <hook.h>
#include <base/base.h>
#include <Level/LevelData.h>
#include <Packet/ResourcePacksInfoPacket.h>

inline struct Settings {
  bool ForceExperimentalGameplay = false;
  bool EducationFeatures         = false;
  bool DebugPacks                = false;
  bool CoResourcePack            = false;

  template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) {
    return f(settings.ForceExperimentalGameplay, node["ForceExperimentalGameplay"]) &&
           f(settings.EducationFeatures, node["EducationFeatures"]) &&
           f(settings.DebugPacks, node["DebugPacks"]) &&
           f(settings.CoResourcePack, node["CoResourcePack"]);
  }
} settings;

DEF_LOGGER("Experimental");