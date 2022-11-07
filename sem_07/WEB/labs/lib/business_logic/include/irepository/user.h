#pragma once

#include "model_bl/user.h"


class IUserRepository
{
public:
    virtual UserBL get_user(int user_id) = 0;
    virtual int get_user_id(UserBL user) = 0;
    virtual UserBL check_user(const std::string &login, const std::string &password) = 0;
    virtual int get_user_id(const std::string &login, const std::string &password) = 0;
    virtual std::vector<UserBL> get_users() = 0;
    virtual UserBL add_user(std::string name, std::string surname, std::string login,
                            std::string password, std::string city, std::string access) = 0;
    virtual UserBL delete_user(int user_id) = 0;
    virtual UserBL update_user(int user_id, const std::string& name, const std::string& surname, 
                               const std::string& login, const std::string& password, const std::string& city) = 0;
    virtual UserBL update_user(UserBL user, const std::string& name, const std::string& surname, 
                               const std::string& login, const std::string& password, const std::string& city) = 0;
};
