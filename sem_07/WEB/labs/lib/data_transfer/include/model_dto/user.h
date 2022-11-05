#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "model_bl/user.h"


class UserDTO
{
public:
    UserDTO(int id, std::string full_name, std::string login, std::string city, std::string access):
        _id(id), _full_name(std::move(full_name)), _login(std::move(login)), 
        _city(std::move(city)), _access(std::move(access)) {}
    UserDTO(int user_id, UserBL user_bl);
    UserDTO() = default;

    int get_id();
    std::string get_full_name();
    std::string get_login();
    std::string get_city();
    std::string get_access();

    explicit operator bool() const { return !_login.empty(); }
    bool operator == (UserDTO user) const
    {
        return user.get_id() == _id;
    }

private:
    int _id;
    std::string _full_name;
    std::string _login;
    std::string _city;
    std::string _access;
};
