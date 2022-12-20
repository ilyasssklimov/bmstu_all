#pragma once

#include <algorithm>
#include "service/client.h"


class UserRepository: public IUserRepository
{
public:
    UserRepository(std::vector<UserBL> users): _users(users) {}

    UserBL get_user(int user_id) override;
    int get_user_id(UserBL user) override;
    int get_user_id(const std::string &login, const std::string &password) override;
    UserBL check_user(const std::string &login, const std::string &password) override;
    
    std::vector<UserBL> get_users() override;
    UserBL add_user(std::string name, std::string surname, std::string login,
                    std::string password, std::string city, std::string access) override;
    UserBL delete_user(int user_id) override;
    
    UserBL update_user(int user_id, const std::string& name, const std::string& surname, 
                       const std::string& login, const std::string& password, 
                       const std::string& city) override;
    UserBL update_user(UserBL user, const std::string& name, const std::string& surname, const std::string& login,
                       const std::string& password, const std::string& city) override;

private:
    std::vector<UserBL> _users;
};
