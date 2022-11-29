#include <iostream>
#include <filesystem>
#include <thread>
#include <fstream>
#include <iterator>

#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include <SQLiteCpp/SQLiteCpp.h>

#include <Core/DedicatedServer.h>

#include <hook.h>
#include <yaml.h>
#include <dllentry.h>
#include <modutils.h>
#include <base/base.h>
#include <base/log.h>

#include "settings.hpp"
#include "loader.h"

Settings settings;

THook(void*, "??R?$default_delete@VConsoleInputReader@@@std@@QEBAXPEAVConsoleInputReader@@@Z", void *self, char *s) {
  	auto &thrd = directAccess<std::thread>(s, 0x58);
  	if (thrd.joinable()) { thrd.detach(); }
  	return original(self, s);
}

static bool stopping = false;

static BOOL ConsoleCtrlHandler(DWORD type) {
	DEF_LOGGER("ConsoleCtrlHandler");
	if (type == CTRL_C_EVENT) {
		auto dedicatedServer = LocateService<DedicatedServer>();
		if (dedicatedServer) {
			if (stopping) return TRUE;
			dedicatedServer->doAsyncStop();
			LOGW("Requested to stop");
			stopping = true;
			return TRUE;
		}
		ExitProcess(0);
	}
	return TRUE;
}

class MBuf : public std::stringbuf {
public:
  	int sync() {
		fputs(str().c_str(), stdout);
		str("");
		return 0;
  	}
} buf;

void dllenter() {
  	using namespace std::filesystem;
  	DEF_LOGGER("Base");
  	SetDllDirectory(L"Mods");
  	SetConsoleCP(65001);
  	SetConsoleOutputCP(65001);
  	SetConsoleMode(
	  	GetStdHandle(STD_OUTPUT_HANDLE),
	  	ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
  	std::cout.rdbuf(&buf);

  	std::thread::id this_id = std::this_thread::get_id();
  	LOGV("Current thread id: %d") % this_id;
  	LOGI("Base mod loaded, setting up CtrlC handler...");
  	SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

  	try {
		auto cfg     = readConfig();
		bool changed = !ReadYAML(settings, cfg);
		if (changed) WriteYAML(settings, cfg);
		auto mods = cfg["mods"];
		initDatabase();
		if (settings.ModEnabled) loadMods(mods);
		writeConfig(cfg);
  	}
	catch (std::exception const &e) {
		LOGE("Unexcepted exception: %s") % e.what();
	}
}
void dllexit() {}