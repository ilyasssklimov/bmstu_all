#pragma once

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
