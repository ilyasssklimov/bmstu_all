#ifndef TEST_USER_REPOSITORY_H
#define TEST_USER_REPOSITORY_H

#include <algorithm>
#include "controller/client.h"


class UserRepository: public IUserRepository
{
public:
    UserRepository(std::vector<UserBL> users): _users(users) {}

    virtual UserBL get_user(int user_id)
    {
        return _users[user_id];
    }

    virtual int get_user_id(UserBL user)
    {
        return std::distance(_users.begin(), std::find(_users.begin(), _users.end(), user));
    }

    virtual UserBL check_user(const std::string &login, const std::string &password)
    {
        for (UserBL user: _users)
            if (user.get_login() == login && user.get_password() == password)
                return user;

        return {};
    }

    virtual std::vector<UserBL> get_users()
    {
        return _users;
    }

    virtual UserBL add_user(std::string name, std::string surname, std::string login,
                            std::string password, std::string city, std::string access)
    {
        UserBL user(name, surname, login, password, city, access);
        _users.push_back(user);
        return user;
    }

    virtual UserBL delete_user(int user_id)
    {
        UserBL user = _users[user_id];
        _users.erase(_users.begin() + user_id);
        return user;
    }

    virtual UserBL update_user(int user_id, std::string name, std::string surname, std::string login,
                               std::string password, std::string city, std::vector<PostBL> posts, bool upd_posts)
    {
        UserBL user = _users[user_id];

        std::string upd_name;
        if (!name.empty())
            upd_name = name;
        else
            upd_name = user.get_name();

        std::string upd_surname;
        if (!surname.empty())
            upd_surname = surname;
        else
            upd_surname = user.get_surname();

        std::string upd_login;
        if (!login.empty())
            upd_login = login;
        else
            upd_login = user.get_login();

        std::string upd_password;
        if (!password.empty())
            upd_password = password;
        else
            upd_password = user.get_password();

        std::string upd_city;
        if (!city.empty())
            upd_city = city;
        else
            upd_city = user.get_city();

        std::vector<PostBL> upd_vector_posts;
        if (upd_posts)
            upd_vector_posts = posts;
        else
            upd_vector_posts = user.get_posts();

        UserBL upd_user(upd_name, upd_surname, upd_login, upd_password,
                        upd_city, user.get_access(), upd_vector_posts);

        _users[user_id] = upd_user;
        return upd_user;
    }

    UserBL update_user(UserBL user, const std::string& name, const std::string& surname, const std::string& login,
                       const std::string& password, const std::string& city, std::vector<PostBL> posts, bool upd_posts)
    {
        std::vector<UserBL> users = get_users();
        std::vector<UserBL>::iterator user_it = std::find(users.begin(), users.end(), user);
        if (user_it != users.end())
            return update_user(std::distance(users.begin(), user_it),
                               name, surname, login, password, city, posts, upd_posts);
        else
            return {};
    }

private:
    std::vector<UserBL> _users;
};

#endif  // TEST_USER_REPOSITORY_H
