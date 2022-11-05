#pragma once

#include "service/admin.h"
#include "database/database.h"

#include "client.h"
#include "service/admin.h"
#include "database/database.h"


class AdminConsole: public ClientConsole
{
public:
    explicit AdminConsole(AdminService &service, int user_id): 
        ClientConsole(service, user_id), _admin_service(service) {}
    std::string get_admin_menu();
    void switch_admin_menu(int command);

    void submit_post();

protected:
    AdminService _admin_service;
};
