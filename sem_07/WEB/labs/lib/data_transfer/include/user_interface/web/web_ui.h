#pragma once

#include "logger.h"
#include "locator.hpp"

#include "database/database.h"
#include "user_interface/user_interface.h"


class WebUI: public IUserInterface
{
public:
    explicit WebUI(std::shared_ptr<IDataBase> db): IUserInterface(db) {};
    int run() override;

private:
    void instantiate();
};


class Server
{
public:
    explicit Server(std::string port): _port(port) {}

    std::string get_port() { return _port; }

private:
    std::string _port;
};
