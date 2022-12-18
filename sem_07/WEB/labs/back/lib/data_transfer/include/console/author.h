#pragma once

#include "client.h"
#include "service/author.h"
#include "database/database.h"


class AuthorConsole: public ClientConsole
{
public:
    explicit AuthorConsole(AuthorService& service, int user_id): 
        ClientConsole(service, user_id), _author_service(service) {}

    std::string get_author_menu();
    void switch_author_menu(int command);

    void add_post(int user_id);

protected:
    AuthorService _author_service;
};
