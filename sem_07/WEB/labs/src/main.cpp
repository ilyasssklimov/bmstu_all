#include "user_interface/entry_point.h"
#include "user_interface/web/web_ui.h"
#include "database/pg_database_async.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        log_error("Second parameter should be port");
        return 1;
    }
    
    auto server = std::make_shared<Server>(argv[1]);
    ServiceLocator::instantiate<Server>(server);

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    WebUI ui(db);

    RunApplication app(&ui);
    return app.run();
}
