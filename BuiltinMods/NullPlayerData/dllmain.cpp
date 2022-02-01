#include <dllentry.h>
#include <hook.h>
#include <base/log.h>
#include <yaml.h>
#include <Actor/Player.h>

DEF_LOGGER("NullPlayerData");

void dllenter() {}
void dllexit() {}

inline struct Settings {
  bool bypass_op = false;

  template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) {
    return f(settings.bypass_op, node["bypass_op"]);
  }
} settings;

DEFAULT_SETTINGS(settings);

TClasslessInstanceHook(void, "?save@LevelStorage@@QEAAXAEAVActor@@@Z", Player &player) {
  if (settings.bypass_op && player.isOperator()) original(this, player);
}