#pragma once

#include <string>
#include <optional>
#include <functional>
#include <unordered_map>

#include "../dll.h"

class LevelStorage;
struct CommandFlag;

struct EducationLocalLevelSettings {
	std::optional<std::string> mCodeBuilderOverrideUri; // 0x0
	bool mHasQuiz; // 0x28
};

static_assert(sizeof(EducationLocalLevelSettings) == 0x30);

struct EducationLevelSettings {
	std::string mCodeBuilderDefaultUri; // 0x0
	std::string mCodeBuilderTitle; // 0x20
	bool mCanResizeCodeBuilder; // 0x40
	std::unordered_map<std::string, CommandFlag> mHiddenPlayerCommands; // 0x48
	EducationLocalLevelSettings mLocalSettings; // 0x88

	MCAPI EducationLevelSettings();
	MCAPI EducationLevelSettings(EducationLevelSettings const &);

	MCAPI EducationLevelSettings &operator=(EducationLevelSettings const &);

	//?getCommandOverrideFunctor@EducationLevelSettings@@QEBA?AV?$function@$$A6AXAEAUCommandFlag@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z@std@@XZ
	MCAPI std::function<void(CommandFlag &, std::string const &)> getCommandOverrideFunctor() const;

	MCAPI static std::optional<EducationLevelSettings> load(LevelStorage const &);
};

static_assert(sizeof(EducationLevelSettings) == 0xB8);