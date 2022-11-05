#pragma once

#include "database/database.h"
#include "user_interface.h"


class RunApplication
{
public:
    explicit RunApplication(IUserInterface* ui): _ui(ui) {};
    int run();

private:
    IUserInterface* _ui;
};
