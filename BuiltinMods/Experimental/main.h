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
	bool forceExperimentalGameplay = false;
	bool educationFeatures         = false;
	bool debugPacks                = false;
	bool coResourcePack            = false;

	template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) {
		return f(settings.forceExperimentalGameplay, node["forceExperimentalGameplay"]) &&
				f(settings.educationFeatures, node["educationFeatures"]) &&
				f(settings.debugPacks, node["debugPacks"]) &&
				f(settings.coResourcePack, node["coResourcePack"]);
	}
} settings;

DEF_LOGGER("Experimental");