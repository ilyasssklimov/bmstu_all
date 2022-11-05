#include "logger.h"
#include "user_interface/entry_point.h"


int RunApplication::run()
{
    log_info("Starting application");
    return _ui->run();
}
