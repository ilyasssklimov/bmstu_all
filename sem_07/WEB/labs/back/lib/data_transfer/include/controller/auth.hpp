#pragma once

#include <memory>
#include "locator.hpp"
#include "service/auth.h"
#include "jwt/jwt.h"
#include "controller/guest.hpp"
#include "model_dto/auth.h"


class AuthController
{
public:
    explicit AuthController(std::shared_ptr<AuthService> service): _auth_service(service) {};
    explicit AuthController();
    
    std::string generate_token(int user_id);
    std::string generate_token(std::string login, std::string password);
    bool verify_token(std::string token);
    int get_id(std::string token);
    std::string get_access(int user_id);

private:
    std::shared_ptr<AuthService> _auth_service;
    JWT get_jwt(std::string token, int& id);
};


using oatpp::web::server::handler::AuthorizationObject;
class BearerAuthHandler: public oatpp::web::server::handler::BearerAuthorizationHandler 
{
public:
    BearerAuthHandler(): oatpp::web::server::handler::BearerAuthorizationHandler("JWT-auth") {}
    std::shared_ptr<AuthorizationObject> authorize(const oatpp::String& token) override;
};


#include OATPP_CODEGEN_BEGIN(ApiController)

class OatppAuthController: public oatpp::web::server::api::ApiController 
{
public:
    OatppAuthController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)): 
        oatpp::web::server::api::ApiController(objectMapper) {}

    ADD_CORS(sign_up)
    ENDPOINT_INFO(sign_up) 
    {
        info->summary = "User registration";
        info->addResponse<Object<AuthOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Some field is empty or access is not 'C' or 'A'");
        info->addResponse<String>(Status::CODE_502, "text/plain", "There is user with such login");
        info->tags.push_back("Auth");
    }
    ENDPOINT("POST", "/api/v1/register", sign_up, BODY_DTO(Object<NewUserOatpp>, user))
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();

        std::string name = user->name;
        std::string surname = user->surname;
        std::string login = user->login;
        std::string password = user->password;
        std::string city = user->city;
        std::string access = user->access;

        if (name.empty() || surname.empty() || login.empty() || password.empty() || city.empty() || access.empty()
            || (access != "C" && access != "A"))
            return createResponse(Status::CODE_400, "ERROR");

        UserDTO user_dto = guest_controller->sign_up(name, surname, login, password, city, access);
        if (user_dto)
        {
            auto auth = AuthOatpp::createShared();
            int user_id = user_dto.get_id();
            auth->token = ServiceLocator::resolve<AuthController>()->generate_token(user_id);
            
            return createDtoResponse(Status::CODE_200, auth);
        }

        return createResponse(Status::CODE_502, "ERROR");
    }


    ADD_CORS(sign_in)
    ENDPOINT_INFO(sign_in) 
    {
        info->summary = "User authorization";
        info->addResponse<Object<AuthOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Incorrect login / password");
        info->tags.push_back("Auth");
    }
    ENDPOINT("POST", "/api/v1/login", sign_in, BODY_DTO(Object<AuthUserOatpp>, user))
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();

        std::string login = user->login;
        std::string password = user->password;
        std::string token = ServiceLocator::resolve<AuthController>()->generate_token(login, password);

        if (!token.empty())
        {
            auto auth = AuthOatpp::createShared();
            auth->token = token;
            return createDtoResponse(Status::CODE_200, auth);
        }
       
        return createResponse(Status::CODE_401, "ERROR");
    }
};

#include OATPP_CODEGEN_END(ApiController)
