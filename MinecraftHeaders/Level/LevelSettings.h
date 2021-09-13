#pragma once

#include "../Level/GameType.h"
#include "../Level/Difficulty.h"

class LevelSettings {
public:
    unsigned int seed;
    GameType gameType;
    Difficulty difficulty;
};