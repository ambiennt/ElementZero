#include "main.h"
#include <dllentry.h>

DEFAULT_SETTINGS(settings);

TClasslessInstanceHook(bool, "?isEnabled@FeatureToggles@@QEBA_NW4FeatureOptionID@@@Z", FeatureOptionID id) {
	if (settings.forceExperimentalGameplay) return true;
	return original(this, id); // only checks for FeatureOptionID::Scoreboards and FeatureOptionID::ExternalWorldTemplatePackSources
}

THook(bool, "?isBaseCodeBuilderEnabled@EducationOptions@@SA_NXZ") {
	if (settings.educationFeatures) return true;
	return original();
}

THook(bool, "?isChemistryEnabled@EducationOptions@@SA_NXZ") {
	if (settings.educationFeatures) return true;
	return original();
}

THook(bool, "?isCodeBuilderEnabled@EducationOptions@@SA_NXZ") {
	if (settings.educationFeatures) return true;
	return original();
}

TClasslessInstanceHook(bool, "?hasExperimentalGameplayEnabled@LevelData@@QEBA_NXZ", int id) {
	if (settings.forceExperimentalGameplay) return true;
	return original(this, id);
}

TClasslessInstanceHook(bool, "?hasExperimentalGameplayEnabled@Level@@QEBA_NXZ", int id) {
	if (settings.forceExperimentalGameplay) return true;
	return original(this, id);
}

TClasslessInstanceHook(LevelData,
	"?getLevelData@ExternalFileLevelStorageSource@@UEBA?AVLevelData@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
	std::string const &levelId) {
	auto data                                = original(this, levelId);
	data.mEducationFeaturesEnabled           = settings.educationFeatures;
	data.mGameRules.rules[18].value.val_bool = settings.forceExperimentalGameplay;
	return data;
}

TClasslessInstanceHook(void, "?forEachIn@ResourcePack@@QEBAXAEBVPath@Core@@V?$function@$$A6AXAEBVPath@Core@@@Z@std@@H_N@Z",
	Core::Path const &path, std::function<void(Core::Path const &)> fn, int a, bool flag) {
	if (settings.debugPacks) {
		DEF_LOGGER("PACK DEBUG");
		LOGV("loaded packs: %p %p %d %d") % (void *) this % path.data % a % flag;
		original(
				this, path,
				[=](auto const &path) {
					LOGV("\t%s") % path.data;
					fn(path);
				},
				a, flag);
	} else {
		original(this, path, fn, a, flag);
	}
}

THook(void, "?write@ResourcePacksInfoPacket@@UEBAXAEAVBinaryStream@@@Z", ResourcePacksInfoPacket &pkt, BinaryStream &stream) {
	pkt.mData.mForceServerPacks = settings.coResourcePack;
	original(pkt, stream);
}