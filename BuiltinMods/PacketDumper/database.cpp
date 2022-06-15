#include <memory>

#include <SQLiteCpp/Database.h>
#include <base/log.h>
#include "global.h"

DEF_LOGGER("PacketDumper");

void InitDatabase() {
  database = std::make_unique<SQLite::Database>(settings.Database, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  database->exec("PRAGMA journal_mode = WAL");
  database->exec("PRAGMA synchronous = NORMAL");
  database->exec(
    "CREATE TABLE IF NOT EXISTS idmap ("
    "session BLOB CHECK(length(session) = 16), "
    "netid INT, "
    "address TEXT, "
    "xuid INT, "
    "PRIMARY KEY(session, netid))"
  );
  database->exec(
    "CREATE TABLE IF NOT EXISTS packets ("
    "session BLOB CHECK(length(session) = 16), "
    "netid INT, "
    "time DATETIME DEFAULT(STRFTIME('%Y-%m-%d %H:%M:%f', 'now')), "
    "type BOOLEAN CHECK(type = 0 OR type = 1), "
    "data BLOB)"
  );
}