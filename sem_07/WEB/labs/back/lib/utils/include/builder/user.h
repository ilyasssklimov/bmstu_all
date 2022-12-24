#pragma once

#include "model_bl/user.h"


class UserBuilder 
{
public:
    explicit UserBuilder();
    UserBL build(bool random=true);

    UserBuilder with_name(std::string name);
    UserBuilder with_surname(std::string surname);
    UserBuilder with_login(std::string login);
    UserBuilder with_password(std::string password);
    UserBuilder with_city(std::string city);
    UserBuilder with_access(std::string access);

private:
    std::string _name = "name_";
    std::string _surname = "surname_";
    std::string _login = "login_";
    std::string _password = "password_";
    std::string _city = "city_";
    std::string _access = "C";

    std::vector<std::string> _roles;
    std::string get_random();
};