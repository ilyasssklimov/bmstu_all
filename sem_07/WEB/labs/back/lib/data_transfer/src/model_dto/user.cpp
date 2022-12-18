#include "model_dto/user.h"


UserDTO::UserDTO(int id, UserBL user_bl)
{   
    _id = id;
    _full_name = user_bl.get_name() + " " + user_bl.get_surname();
    _login = user_bl.get_login();
    _city = user_bl.get_city();
    _access = user_bl.get_access();
}


int UserDTO::get_id()
{
    return _id;
}

std::string UserDTO::get_full_name()
{
    return _full_name;
}


std::string UserDTO::get_login()
{
    return _login;
}


std::string UserDTO::get_city()
{
    return _city;
}


std::string UserDTO::get_access()
{
    return _access;
}


oatpp::Object<UserOatpp> UserDTO::get_oatpp_object()
{
    auto user = UserOatpp::createShared();

    user->id = get_id();
    user->full_name = get_full_name();         
    user->login = get_login();
    user->city = get_city();
    user->access = get_access();

    return user;
}


oatpp::Object<UsersOatpp> UserDTO::get_oatpp_users(std::vector<UserDTO> users_dto)
{
    auto users = UsersOatpp::createShared();
    users->users = {};

    for (auto& user_dto: users_dto)
    {
        auto user = user_dto.get_oatpp_object();
        users->users->push_back(user);
    }

    return users;
}
