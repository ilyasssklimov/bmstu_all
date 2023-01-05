#include <algorithm>
#include "test_repository/user.h"


UserBL TestUserRepository::get_user(int user_id)
{
    return _users[user_id];
}


int TestUserRepository::get_user_id(UserBL user)
{
    return std::distance(_users.begin(), std::find(_users.begin(), _users.end(), user));
}


int TestUserRepository::get_user_id(const std::string &login, const std::string &password)
{
    for (unsigned i = 0; i < _users.size(); i++)
        if (_users[i].get_login() == login && _users[i].get_password() == password)
            return i;

    return {};
}


UserBL TestUserRepository::check_user(const std::string &login, const std::string &password)
{
    for (UserBL user: _users)
        if (user.get_login() == login && user.get_password() == password)
            return user;

    return {};
}


std::vector<UserBL> TestUserRepository::get_users()
{
    std::cout << "Fake repo (getting users)\n";
    return _users;
}


UserBL TestUserRepository::add_user(std::string name, std::string surname, std::string login,
                                    std::string password, std::string city, std::string access)
{
    UserBL user(name, surname, login, password, city, access);
    _users.push_back(user);
    return user;
}


UserBL TestUserRepository::delete_user(int user_id)
{
    UserBL user = _users[user_id];
    _users.erase(_users.begin() + user_id);
    return user;
}


UserBL TestUserRepository::update_user(int user_id, const std::string& name, const std::string& surname, 
                                       const std::string& login, const std::string& password, 
                                       const std::string& city)
{
    UserBL user = _users[user_id];

    std::string upd_name = name.empty() ? user.get_name() : name;
    std::string upd_surname = surname.empty() ? user.get_surname() : surname;
    std::string upd_login = login.empty() ? user.get_login() : login;
    std::string upd_password = password.empty() ? user.get_password() : password;
    std::string upd_city = city.empty() ? user.get_city() : city;

    UserBL upd_user(upd_name, upd_surname, upd_login, upd_password, upd_city, user.get_access());
    _users[user_id] = upd_user;

    return upd_user;
}


UserBL TestUserRepository::update_user(UserBL user, const std::string& name, const std::string& surname, 
                                       const std::string& login, const std::string& password, const std::string& city)
{
    std::vector<UserBL> users = get_users();
    std::vector<UserBL>::iterator user_it = std::find(users.begin(), users.end(), user);

    if (user_it != users.end())
        return update_user(std::distance(users.begin(), user_it), name, surname, login, password, city);

    return {};
}
