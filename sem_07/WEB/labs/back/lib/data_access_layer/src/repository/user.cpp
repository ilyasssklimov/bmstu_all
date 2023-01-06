#include <utility>
#include "exception.h"
#include "repository/user.h"
#include "logger.h"
#include "locator.hpp"


UserRepository::UserRepository()
{
    _db = ServiceLocator::resolve<IDataBase>();

    if (!_db)
    {
        log_error("There are not db for UserRepository");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }
}


UserBL UserRepository::user_to_user_bl(User user)
{
    UserBL user_bl = UserBL(user.get_name(), user.get_surname(), user.get_login(),
                            user.get_password(),user.get_city(), user.get_access());
    return user_bl;
}


UserBL UserRepository::get_user(int user_id)
{
    User user = _db->get_user(user_id);
    if (!user)
    {
        time_t time_now = time(nullptr);
        throw UserGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(user);
}


int UserRepository::get_user_id(UserBL user)
{
    int user_id = _db->get_user_id(user.get_login());
    if (user_id == -1)
    {
        time_t time_now = time(nullptr);
        throw UserGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_id;
}


UserBL UserRepository::check_user(const std::string &login, const std::string &password)
{
    User user = _db->get_user(login, password);
    if (user)
        return user_to_user_bl(user);
    else
        return {};
}


int UserRepository::get_user_id(const std::string &login, const std::string &password)
{
    int user_id = _db->get_user_id(login, password);
    
    if (user_id == -1)
    {
        time_t time_now = time(nullptr);
        throw UserGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_id;
}


std::vector<UserBL> UserRepository::get_users()
{
    std::vector<User> users = _db->get_users();

    std::vector<UserBL> users_bl;
    for (auto &user: users)
    {
        UserBL user_bl = user_to_user_bl(user);
        users_bl.push_back(user_bl);
    }

    return users_bl;
}


UserBL UserRepository::add_user(std::string name, std::string surname, std::string login,
                                std::string password, std::string city, std::string access)
{
    User user = _db->add_user(name, surname, login, password, city, access);
    if (!user)
    {
        time_t time_now = time(nullptr);
        throw UserAddException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(user);
}


UserBL UserRepository::delete_user(int user_id)
{
    User user = _db->delete_user(user_id);
    if (!user)
    {
        time_t time_now = time(nullptr);
        throw UserAddException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(user);
}


UserBL UserRepository::update_user(int user_id, const std::string& name, const std::string& surname, 
                                   const std::string& login, const std::string& password, const std::string& city)
{
    UserBL user = get_user(user_id);

    std::string upd_name = name.empty() ? user.get_name() : name;
    std::string upd_surname = surname.empty() ? user.get_surname() : surname;
    std::string upd_login = login.empty() ? user.get_login() : login;
    std::string upd_password = password.empty() ? user.get_password() : password;
    std::string upd_city = city.empty() ? user.get_city() : city;

    User upd_user = _db->update_user(user_id, upd_name, upd_surname, upd_login, upd_password, upd_city);

    if (!upd_user)
    {
        time_t time_now = time(nullptr);
        throw UserUpdateException(__FILE__, __LINE__, ctime(&time_now));
    }

    return user_to_user_bl(upd_user);
}


UserBL UserRepository::update_user(UserBL user, const std::string& name, const std::string& surname, 
                                   const std::string& login, const std::string& password, const std::string& city)
{
    int user_id = get_user_id(user);
    return update_user(user_id, name, surname, login, password, city);
}
