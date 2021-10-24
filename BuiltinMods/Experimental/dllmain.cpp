#include "main.h"
#include <dllentry.h>

DEFAULT_SETTINGS(settings);

 /*enum class FeatureOptionId {
  None                             = 0,
  NetworkLogAllPackets             = 1, // Enable Packet Profiling
  Scoreboards                      = 2, // Scoreboards
  Functions                        = 3, // Functions
  UIAsyncLoadingAndAnimations      = 4, // UI Async Loading and Screen Animations
  Allow3rdPartyServerSplitscreen   = 5, // Allow 3rd Party Server Splitscreen
  ExperimentalGameplayInAllWorlds  = 6, // Default new worlds to be experimental on
  Hummingbird                      = 7, // New Scripting and UI Infrastructure (requires restart)
  HummingbirdDebugging             = 8, // Enable Hummingbird Debugging (requires restart and the infrastructure)
  UIRefresh                        = 9, // Experimental UI (requires the infrastructure)
  Scripting                        = 10, // Experimental Scripting (requires restart and the infrastructure)
  Realms                           = 11, // Realms Enabled
  RealmsContent                    = 12, // Realms Content
  EnableLoadTimer                  = 13, // Enable Load Timers
  ExternalWorldTemplatePackSources = 14, // External World Template Pack Sources
  Win10Subscriptions               = 15, // Enable Win10 subscriptions
  PlayerRenaming                   = 16, // Enable Player Renaming After Sign-in (requires restart)
  PersonaBackend                   = 17, // ***DOES NOT EXIST***
  PersonaSkin                      = 18, // ***DOES NOT EXIST***
  PlayFabInsightsTelemetry         = 19, // Enable PlayFab Insights (requires restart)
  PersonaEnabled                   = 20, // Enable Persona
  PersonaServiceEnabled            = 21, // Enable Persona Service
  PersonaTestCatalog               = 22, // Enable Persona Testing Resource Pack
  PersonaCape                      = 23, // ***DOES NOT EXIST***
  PersonaFeatures                  = 24, // Enable Persona Features
  PersonaChallengeFeature          = 25, // Enable Persona Challenge Feature
  StorefrontTestLayouts            = 26, // Enable Store Test Layouts
  UseDevOffersIfAvailable          = 27, // Enable Dev Offers
  RenderDragonRenderPath           = 28, // Experimental Render Path
  BaseGameVersioniningTestPacks    = 29, // Enables the use of test packs for base game versioning
  LevelStoragePerfLog              = 30, // ***DOES NOT EXIST***
  TrueTypeFontLoading              = 31, // Load true type fonts specified in font_metadata.json when booting the application
  EnableItemStackNetManager        = 32, // Enable ItemStackNetManager (requires server restart)
  PauseMenuOnFocusLost             = 33 // Show the pause menu screen upon the app losing focus
};

TClasslessInstanceHook(bool, "?isEnabled@FeatureToggles@@QEBA_NW4FeatureOptionID@@@Z", int id) {
  if (settings.ForceExperimentalGameplay) return true;
  return original(this, id); // only checks for FeatureOptionId::Scoreboards and FeatureOptionId::ExternalWorldTemplatePackSources
}*/

THook(bool, "?isBaseCodeBuilderEnabled@EducationOptions@@SA_NXZ") {
  if (settings.EducationFeatures) return true;
  return original();
}

THook(bool, "?isChemistryEnabled@EducationOptions@@SA_NXZ") {
  if (settings.EducationFeatures) return true;
  return original();
}

THook(bool, "?isCodeBuilderEnabled@EducationOptions@@SA_NXZ") {
  if (settings.EducationFeatures) return true;
  return original();
}

TClasslessInstanceHook(bool, "?hasExperimentalGameplayEnabled@LevelData@@QEBA_NXZ", int id) {
  if (settings.ForceExperimentalGameplay) return true;
  return original(this, id);
}

TClasslessInstanceHook(bool, "?hasExperimentalGameplayEnabled@Level@@QEBA_NXZ", int id) {
  if (settings.ForceExperimentalGameplay) return true;
  return original(this, id);
}

TClasslessInstanceHook(LevelData,
    "?getLevelData@ExternalFileLevelStorageSource@@UEBA?AVLevelData@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
    std::string const &level_name) {
  auto data                                = original(this, level_name);
  data.mEducationFeaturesEnabled           = settings.EducationFeatures;
  data.mGameRules.rules[18].value.val_bool = true;
  return data;
}

TClasslessInstanceHook(void, "?forEachIn@ResourcePack@@QEBAXAEBVPath@Core@@V?$function@$$A6AXAEBVPath@Core@@@Z@std@@H_N@Z",
    Core::Path const &path, std::function<void(Core::Path const &)> fn, int a, bool flag) {
  if (settings.DebugPacks) {
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
  pkt.data.mHasExceptions = settings.CoResourcePack;
  original(pkt, stream);
}