#include <dllentry.h>
#include <hook.h>
#include <yaml.h>
#include <base/log.h>

DEF_LOGGER("CrashHandler");

void dllenter() {}
void dllexit() {}

inline struct Settings {

    std::string URI;

    template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) {
        return f(settings.URI, node["URI"]);
    }
} settings;

DEFAULT_SETTINGS(settings);

THook(void, "?initialize@CrashHandler@@SAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z",
    std::string const &serverId, std::string const crashUploadUri, std::string const &sessionId) {
    
  LOGV("Crash report endpoint replaced");
  original(serverId, settings.URI, sessionId);
}