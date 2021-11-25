#pragma once

#include <hook.h>
#include <modutils.h>
#include <Scoreboard/Objective.h>
#include <Scoreboard/ScoreboardId.h>

struct ScoreInfo {
	Objective *mObjective;
	bool mValid;
	int mValue;
	int getcount() { return mValue; }
};

static_assert(sizeof(ScoreInfo) == 0x10);