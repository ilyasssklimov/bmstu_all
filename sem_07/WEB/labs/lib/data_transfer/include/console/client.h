#pragma once

#include "service/client.h"
#include "guest.h"


class ClientConsole: public GuestConsole
{
public:
    explicit ClientConsole(ClientService& service, int user_id): 
        GuestConsole(service), _client_service(service), _id(user_id) {}

    std::string get_client_menu();
    void switch_client_menu(int command);

    void show_posts_filters();
    void add_comment(int user_id);
    void show_full_post();
    void show_organizer();

protected:
    ClientService _client_service;
    int _id;
};
