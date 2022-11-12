#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "model_bl/user.h"


#include OATPP_CODEGEN_BEGIN(DTO)  // =============================================================

class UserOatpp: public oatpp::DTO 
{  
    DTO_INIT(UserOatpp, DTO)

    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, full_name);
    DTO_FIELD(String, login);
    DTO_FIELD(String, city);
    DTO_FIELD(String, access);
};

class UsersOatpp: public oatpp::DTO 
{  
    DTO_INIT(UsersOatpp, DTO)
    DTO_FIELD(List<Object<UserOatpp>>, users);
};


class UpdUserOatpp: public oatpp::DTO 
{  
    DTO_INIT(UpdUserOatpp, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD(String, surname);
    DTO_FIELD(String, login);
    DTO_FIELD(String, password);
    DTO_FIELD(String, city);
};

#include OATPP_CODEGEN_END(DTO)  // ===============================================================


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

    oatpp::Object<UserOatpp> get_oatpp_object();
    static oatpp::Object<UsersOatpp> get_oatpp_users(std::vector<UserDTO> users_dto);

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
