#include <dllentry.h>
#include <hook.h>
#include <yaml.h>
#include <base/log.h>

DEF_LOGGER("CrashHandler");

void dllenter() {}
void dllexit() {}

inline struct Settings {

    std::string URI;
    bool disableCrashReportHttpRequest = true;

    template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) {
        return f(settings.URI, node["URI"]) &&
               f(settings.disableCrashReportHttpRequest, node["disableCrashReportHttpRequest"]);
    }
} settings;

DEFAULT_SETTINGS(settings);



THook(void, "?initialize@CrashHandler@@SAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@00@Z",
    std::string const &serverId, std::string const crashUploadUri, std::string const &sessionId) {
    LOGI("Crash report endpoint replaced to %s") % settings.URI;
    original(serverId, settings.URI, sessionId);
}

THook(void, "?SendCrashReport@CrashReportSender@google_breakpad@@QEAA?AW4ReportResult@2@AEBV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@AEBV?$map@V?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@V12@U?$less@V?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@V12@@std@@@2@@5@1PEAV45@@Z",
    wchar_t *FileName, void* lpszUrl, int64_t a3, int64_t a4, int64_t a5) {
    if (settings.disableCrashReportHttpRequest) return;
    original(FileName, lpszUrl, a3, a4, a5);
}