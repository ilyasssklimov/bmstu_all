#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "model_bl/user.h"
#include "irepository/user.h"
#include "locator.hpp"


class AuthService
{
public:    
    explicit AuthService(std::shared_ptr<IUserRepository> user_repo): _user_repo(user_repo) {}
    explicit AuthService();

    std::string get_password(int user_id);
    std::string get_access(int user_id);
    int get_user_id(const std::string &login, const std::string &password);

protected:
    std::shared_ptr<IUserRepository> _user_repo;
};
