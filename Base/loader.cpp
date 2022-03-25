#include <exception>
#include <filesystem>
#include <list>
#include <unordered_set>

#include <Windows.h>
#include <Psapi.h>

#include <Command/CommandOrigin.h>
#include <Command/CommandOutput.h>

#include <hook.h>

#include <base/base.h>
#include <base/log.h>

#include "loader.h"
#include "settings.hpp"
#include "yaml.h"

using namespace std::filesystem;

DEF_LOGGER("ModLoader");

typedef void (*ApplySettingsType)(YAML::Node const &);
typedef bool (*GenerateSettingsType)(YAML::Node &);
typedef void (*PrePostInitType)();
typedef void (*WorldInitType)(std::filesystem::path const &);
typedef void (*ServerStartType)();
typedef void (*BeforeUnloadType)();
typedef void (*AfterReloadType)();

class lc_string {
  std::string data;

public:
  operator std::string &() { return data; }
  operator std::string const &() const { return data; }

  lc_string(char const *init) { std::transform(init, init + strlen(init), std::back_inserter(data), &::tolower); }
  lc_string(std::string const &inp) { std::transform(inp.begin(), inp.end(), std::back_inserter(data), &::tolower); }

  bool operator<(lc_string const &rhs) const { return data < rhs.data; }
};

using lc_set = std::set<lc_string>;

struct ModLibrary {
  lc_string name;
  std::string keyname;
  HMODULE handle;

  ModLibrary(lc_string str) : name(str) {}

  ApplySettingsType applySettings;
  GenerateSettingsType generateSettings;
  PrePostInitType preInit, postInit;
  WorldInitType worldInit;
  ServerStartType serverStart;
  BeforeUnloadType beforeUnload;
  AfterReloadType afterReload;

  lc_set dependencies;
};

template <typename Fn, Fn(ModLibrary::*Field)> struct FnWithName {
  std::string name;
  Fn fn;

  FnWithName(ModLibrary const &src) : name(src.keyname), fn(src.*Field) {}

  template <typename... Ps> void operator()(Ps &&... ps) { fn(std::forward<Ps>(ps)...); }
};

struct ReloadableMod {
  std::string name;
  ApplySettingsType applySettings;
  GenerateSettingsType generateSettings;
  AfterReloadType afterReload;

  ReloadableMod(ModLibrary const &src)
      : name(src.keyname), applySettings(src.applySettings), generateSettings(src.generateSettings),
        afterReload(src.afterReload) {}

  void operator()(YAML::Node &node) {
    applySettings(node);
    generateSettings(node);
    afterReload();
  }
};

static std::map<lc_string, HMODULE> LoadedMods;
static std::list<ModLibrary> LibList;
static std::list<FnWithName<PrePostInitType, &ModLibrary::postInit>> PostInits;
static std::list<FnWithName<WorldInitType, &ModLibrary::worldInit>> WorldInits;
static std::list<FnWithName<ServerStartType, &ModLibrary::serverStart>> ServerStarts;
static std::list<FnWithName<BeforeUnloadType, &ModLibrary::beforeUnload>> UnloadHooks;
static std::list<ReloadableMod> Reloadables;
static lc_set LibNameList;

HMODULE GetLoadedMod(const char *name) {
  auto it = LoadedMods.find(lc_string{name});
  if (it == LoadedMods.end()) return 0;
  return it->second;
}

static void doLoadLib(YAML::Node &cfg_node, ModLibrary const &lib);

void loadMods(YAML::Node &cfg_node) {
  LOGI("Starting to load mods");
  std::error_code ec;
  for (directory_iterator next("mods", directory_options::follow_directory_symlink, ec), end; next != end; ++next) {
    if (next->is_regular_file() && next->path().extension() == ".dll") {
      const auto cfgkey = next->path().stem().string();
      auto subcfg       = cfg_node[cfgkey];
      if (subcfg.IsMap()) {
        auto enabled = subcfg["enabled"];
        if (!enabled) {
          enabled = settings.ModDefaultEnabled;
          if (!settings.ModDefaultEnabled) continue;
        } else if (!enabled.as<bool>())
          continue;
      } else {
        subcfg["enabled"] = settings.ModDefaultEnabled;
        if (!settings.ModDefaultEnabled) continue;
      }
      LOGV("Loading %s") % absolute(next->path()).string();
      auto handle = LoadLibrary(next->path().c_str());
      if (!handle) {
        LPSTR messageBuffer = nullptr;
        FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
            GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR) &messageBuffer, 0, NULL);
        LOGE("Failed to load mod: %s: %s") % next->path() % messageBuffer;
        LocalFree(messageBuffer);
        continue;
      }
      auto name = next->path().filename().string();
      ModLibrary lib{name};
      lib.keyname          = cfgkey;
      lib.handle           = handle;
      lib.applySettings    = (ApplySettingsType) GetProcAddress(handle, "ApplySettings");
      lib.generateSettings = (GenerateSettingsType) GetProcAddress(handle, "GenerateSettings");
      lib.preInit          = (PrePostInitType) GetProcAddress(handle, "PreInit");
      lib.postInit         = (PrePostInitType) GetProcAddress(handle, "PostInit");
      lib.worldInit        = (WorldInitType) GetProcAddress(handle, "WorldInit");
      lib.serverStart      = (ServerStartType) GetProcAddress(handle, "ServerStart");
      lib.beforeUnload     = (BeforeUnloadType) GetProcAddress(handle, "BeforeUnload");
      lib.afterReload      = (AfterReloadType) GetProcAddress(handle, "AfterReload");
      LibList.emplace_back(lib);
      LibNameList.emplace(name);
      LOGI("Loaded  %s") % next->path().filename().string();
    }
  }
  if (ec) {
    LOGE("Warning: Cannot open mods folder: %s") % ec.message();
    return;
  }
  auto curproc = GetCurrentProcess();
  for (auto &lib : LibList) {
    MODULEINFO modinfo;
    GetModuleInformation(curproc, lib.handle, &modinfo, sizeof modinfo);

    auto dllbase         = (char *) modinfo.lpBaseOfDll;
    auto dos_header      = (PIMAGE_DOS_HEADER) dllbase;
    auto nt_header       = (PIMAGE_NT_HEADERS)(dllbase + dos_header->e_lfanew);
    auto optional_header = &nt_header->OptionalHeader;
    auto import_desc     = (PIMAGE_IMPORT_DESCRIPTOR)(
        dllbase + optional_header->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    LOGV("Analyzing %s") % (std::string const &) lib.keyname;
    for (auto impit = import_desc; impit->Characteristics; impit++) {
      auto rawname   = (char const *) (dllbase + impit->Name);
      lc_string name = rawname;
      LOGV("\tDepends on %s") % rawname;
      if (LibNameList.count(name) != 0) lib.dependencies.emplace(name);
    }
  }
  while (!LibList.empty()) {
    lc_set cache;
    auto it = LibList.begin();
    while (it != LibList.end()) {
      if (it->dependencies.empty()) {
        doLoadLib(cfg_node, *it);
        cache.emplace(it->name);
        it = LibList.erase(it);
      } else
        ++it;
    }
    for (auto &lib : LibList) {
      lc_set temp;
      std::set_difference(
          lib.dependencies.begin(), lib.dependencies.end(), cache.begin(), cache.end(),
          std::inserter(temp, temp.begin()));
      lib.dependencies = temp;
    }
  }
  for (auto hook : PostInits) try {
      hook();
    } catch (std::exception const &ex) { LOGE("Exception at post init (%s): %s") % hook.name % ex.what(); }
}

void doLoadLib(YAML::Node &cfg_node, ModLibrary const &lib) {
  auto subcfg = cfg_node[lib.keyname];
  LOGI("Init %s") % lib.keyname;
  if (subcfg.IsMap()) {
    if (lib.applySettings) try {
        lib.applySettings(subcfg);
      } catch (std::exception const &ex) { LOGE("Exception at apply settings (%s): %s") % lib.keyname % ex.what(); }
  }
  subcfg["enabled"] = true;
  if (lib.generateSettings) try {
      lib.generateSettings(subcfg);
    } catch (std::exception const &ex) { LOGE("Exception at generate settings (%s): %s") % lib.keyname % ex.what(); }
  if (lib.preInit) try {
      lib.preInit();
    } catch (std::exception const &ex) { LOGE("Exception at pre init (%s): %s") % lib.keyname % ex.what(); }
  if (lib.postInit) PostInits.emplace_back(lib);
  if (lib.worldInit) WorldInits.emplace_back(lib);
  if (lib.serverStart) ServerStarts.emplace_back(lib);
  if (lib.beforeUnload) UnloadHooks.emplace_back(lib);
  if (lib.afterReload) {
    if (lib.applySettings && lib.generateSettings) {
      LOGV("Mod %s is reloadable") % lib.keyname;
      Reloadables.emplace_back(lib);
    } else
      LOGW("Failed to register as reloadable for mod %s") % lib.keyname;
  }
  LoadedMods.emplace(lib.keyname, lib.handle);
}

TClasslessInstanceHook(void, "?leaveGameSync@ServerInstance@@QEAAXXZ") {
  for (auto hook : UnloadHooks) try {
      hook();
    } catch (std::exception const &ex) { LOGE("Exception at unload hook (%s): %s") % hook.name % ex.what(); }
  OnExit();
  original(this);
}

TClasslessInstanceHook(void, "?startServerThread@ServerInstance@@QEAAXXZ") {
  original(this);
  for (auto hook : ServerStarts) try {
      hook();
    } catch (std::exception const &ex) { LOGE("Exception at server start hook (%s): %s") % hook.name % ex.what(); }
}

void worldHook(std::filesystem::path const &path) {
  for (auto hook : WorldInits) try {
      hook(path);
    } catch (std::exception const &ex) { LOGE("Exception at world hook (%s): %s") % hook.name % ex.what(); }
}





TClasslessInstanceHook(void, "?execute@ReloadCommand@@UEBAXAEBVCommandOrigin@@AEAVCommandOutput@@@Z",
  CommandOrigin const &origin, CommandOutput &output) {

  original(this, origin, output);

  auto cfg     = readConfig();
  bool changed = !ReadYAML(settings, cfg);
  if (changed) {
    WriteYAML(settings, cfg);
  }
  auto mods = cfg["mods"];

  for (auto hook : Reloadables) {

    auto content = mods[hook.name];

    if (!content.IsMap()) {
      LOGE("Reload failed for mod %s: cannot find section for mod") % hook.name;
      continue;
    }
    if (!content["enabled"].as<bool>(false)) {
      LOGE("Reload failed for mod %s: cannot disable in runtime") % hook.name;
      continue;
    }

    try {
      hook(content);
      output.addToResultList("mods", hook.name);
    }
    catch (std::exception const &ex) {
      LOGE("Exception at reload hook (%s): %s") % hook.name % ex.what();
    }
  }
  writeConfig(cfg);
}