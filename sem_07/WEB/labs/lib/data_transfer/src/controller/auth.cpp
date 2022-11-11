#include <algorithm>
#include "logger.h"
#include "exception.h"
#include "controller/auth.hpp"


AuthController::AuthController()
{
    _auth_service = ServiceLocator::resolve<AuthService>();

    if (!_auth_service)
    {
        log_error("There are not repositories for AuthController");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }
}
    

std::string AuthController::generate_token(int user_id)
{
    std::string password = _auth_service->get_password(user_id);
    JWT jwt;
    jwt.set_header("\"HS256\"", "\"JWT\"");
    jwt.set_payload({ 
        "sub", "\"Authentication\"",
        "user", std::to_string(user_id)
    });

    std::string token = jwt.generate_token(password);
    token.erase(std::remove(token.begin(), token.end(), '\0'), token.end());
    return token;
}


std::string AuthController::generate_token(std::string login, std::string password)
{    
    int user_id = _auth_service->get_user_id(login, password);

    if (user_id == -1)
        return {};

    return generate_token(user_id);
}    


JWT AuthController::get_jwt(std::string token, int& id)
{
    auto jwt = JWT::get_jwt(token);
    std::string user_id = jwt.get_payload().get_value("user");

    if (user_id.empty())
    {
        time_t time_now = time(nullptr);
        throw JWTException(__FILE__, __LINE__, ctime(&time_now));
    }

    id = std::stoi(user_id);
    return jwt;
}


bool AuthController::verify_token(std::string token)
{
    try
    {
        int user_id;
        auto jwt = get_jwt(token, user_id);
        std::string password = _auth_service->get_password(user_id);

        bool result = jwt.verify(password);
        return result;
    }
    catch (...)
    {
        log_error("Get invalid data in token while verification");
    }

    return false;
}


int AuthController::get_id(std::string token)
{
    try
    {
        int user_id;
        auto jwt = get_jwt(token, user_id);
        return user_id;
    }
    catch (...)
    {
        log_error("Get invalid data in token while verification");
    }

    return -1;
}


std::string AuthController::get_access(int user_id)
{
    log_info("Get access of user with id = " + std::to_string(user_id));
    return _auth_service->get_access(user_id);
}


std::shared_ptr<AuthorizationObject> BearerAuthHandler::authorize(const oatpp::String& token)
{
    auto auth_controller = ServiceLocator::resolve<AuthController>();
    std::string str_token = token->c_str();

    if (!auth_controller->verify_token(str_token))
        return nullptr;

    int user_id = auth_controller->get_id(token);
    auto user = std::make_shared<BearerAuthObject>();
    user->id = user_id;
    user->access = auth_controller->get_access(user_id);
    user->token = token;

    return user;
}
