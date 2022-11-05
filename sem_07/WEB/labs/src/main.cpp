#include "user_interface/entry_point.h"
#include "user_interface/web/web_ui.h"
#include "database/pg_database_async.h"


int main()
{
    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    WebUI ui(db);

    RunApplication app(&ui);
    return app.run();
}
