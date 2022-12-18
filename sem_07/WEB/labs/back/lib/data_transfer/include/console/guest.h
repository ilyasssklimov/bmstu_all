#pragma once

#include "service/guest.h"
#include "database/database.h"


class GuestConsole
{
public:
    explicit GuestConsole(GuestService& service): _guest_service(service) {};

    std::string get_guest_menu();
    UserBL switch_guest_menu(int command);

    UserBL show_posts();
    UserBL show_post_information();
    UserBL sign_in();
    UserBL log_in();

protected:
    GuestService _guest_service;
};
