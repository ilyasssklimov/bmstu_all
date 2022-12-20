#include "builder/user.h"
#include <cstdlib>
#include <ctime>


UserBuilder::UserBuilder() 
{
    _roles = { "C", "A", "M" };
    std::srand((unsigned) std::time(nullptr));
}


std::string UserBuilder::get_random()
{
    return std::to_string(std::rand() % 10 + 1);
}


UserBL UserBuilder::build(bool random) 
{
    if (random)
    {
        _access = _roles[std::rand() % _roles.size()];

        return UserBL(
            _name + get_random(), 
            _surname + get_random(), 
            _login + get_random(),
            _password + get_random(), 
            _city + get_random(),
            _access
        );
    }

    return UserBL(_name, _surname, _login, _password, _city, _access);
}


UserBuilder UserBuilder::with_name(std::string name)
{
    _name = name;
    return *this;
}


UserBuilder UserBuilder::with_surname(std::string surname)
{
    _surname = surname;
    return *this;
}


UserBuilder UserBuilder::with_login(std::string login)
{
    _login = login;
    return *this;
}


UserBuilder UserBuilder::with_password(std::string password)
{
    _password = password;
    return *this;
}


UserBuilder UserBuilder::with_city(std::string city)
{
    _city = city;
    return *this;
}


UserBuilder UserBuilder::with_access(std::string access)
{
    _access = access;
    return *this;
}
