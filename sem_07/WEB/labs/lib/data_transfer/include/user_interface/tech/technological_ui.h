#pragma once

#include "database/database.h"
#include "user_interface/user_interface.h"


class TechnologicalUI: public IUserInterface
{
public:
    explicit TechnologicalUI(std::shared_ptr<IDataBase> db): IUserInterface(db) {};
    int run() override;
};
