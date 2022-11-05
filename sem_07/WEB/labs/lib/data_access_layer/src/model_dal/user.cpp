#include "model_dal/user.h"


std::string User::get_name()
{
    return _name;
}


std::string User::get_surname()
{
    return _surname;
}


std::string User::get_login()
{
    return _login;
}


std::string User::get_password()
{
    return _password;
}


std::string User::get_city()
{
    return _city;
}


std::string User::get_access()
{
    return _access;
}


void User::set_name(const std::string &value)
{
    _name = value;
}


void User::set_surname(const std::string &value)
{
    _surname = value;
}


void User::set_login(const std::string &value)
{
    _login = value;
}


void User::set_password(const std::string &value)
{
    _password = value;
}


void User::set_city(const std::string &value)
{
    _city = value;
}
