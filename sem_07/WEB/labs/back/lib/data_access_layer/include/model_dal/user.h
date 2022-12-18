#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "post.h"


class User
{
public:
    User(std::string name, std::string surname, std::string login, 
         std::string password, std::string city, std::string access):
         _name(std::move(name)), _surname(std::move(surname)), _login(std::move(login)),
         _password(std::move(password)), _city(std::move(city)), _access(std::move(access)) {};
    User() = default;

    std::string get_name();
    std::string get_surname();
    std::string get_login();
    std::string get_password();
    std::string get_city();
    std::string get_access();

    void set_name(const std::string &value);
    void set_surname(const std::string &value);
    void set_login(const std::string &value);
    void set_password(const std::string &value);
    void set_city(const std::string &value);

    explicit operator bool() const { return !_name.empty(); }
    bool operator == (User user) const
    {
        return user.get_name() == _name &&
               user.get_surname() == _surname &&
               user.get_login() == _login &&
               user.get_city() == _city;
    }

private:
    std::string _name;
    std::string _surname;
    std::string _login;
    std::string _password;
    std::string _city;
    std::string _access;
};
