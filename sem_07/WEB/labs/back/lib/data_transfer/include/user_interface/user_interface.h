#pragma once

#include <iostream>
#include <memory>
#include "database/database.h"


class IUserInterface
{
public:
    virtual int run() = 0;

protected:
    explicit IUserInterface(std::shared_ptr<IDataBase> db): _db(db) {};
    std::shared_ptr<IDataBase> _db;
};
