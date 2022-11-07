#pragma once

#include <memory>
#include "locator.hpp"
#include "service/auth.h"
#include "jwt/jwt.h"


class AuthController
{
public:
    explicit AuthController(std::shared_ptr<AuthService> service): _auth_service(service) {};
    explicit AuthController();
    
    std::string generate_token(int user_id);
    std::string generate_token(std::string login, std::string password);
    bool verify_token(std::string token);

protected:
    std::shared_ptr<AuthService> _auth_service;
};
