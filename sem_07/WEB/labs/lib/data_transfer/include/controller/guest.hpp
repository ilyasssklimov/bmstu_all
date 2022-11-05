#pragma once

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include <sstream>
#include <memory>
#include "locator.hpp"
#include "service/guest.h"

#include "model_dto/user.h"
#include "model_dto/post.h"
#include "model_dto/oatpp.hpp"


class GuestController
{
public:
    explicit GuestController(std::shared_ptr<GuestService> service): _guest_service(service) {};
    explicit GuestController();
    
    std::vector<UserDTO> get_users();
    std::vector<PostDTO> get_posts();
    UserDTO get_user(int user_id);
    PostDTO get_post(int post_id);

    UserDTO sign_up(const std::string& name, const std::string& surname, const std::string& login,
                                   const std::string& password, const std::string& city, const std::string& access);
    UserDTO sign_in(const std::string &login, const std::string &password);

protected:
    std::shared_ptr<GuestService> _guest_service;
};


#include OATPP_CODEGEN_BEGIN(ApiController)  // ===================================================

class OatppGuestController: public oatpp::web::server::api::ApiController 
{
public:
    OatppGuestController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    ADD_CORS(users)
    ENDPOINT_INFO(users) 
    {
        info->summary = "Get all users";
        info->addResponse<Object<UsersOatpp>>(Status::CODE_200, "application/json");
        info->tags.push_back("Guest");
    }
    ENDPOINT("GET", "api/v1/users", users) 
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();
        std::vector<UserDTO> users_dto = guest_controller->get_users();

        auto users = UsersOatpp::createShared();
        users->users = {};

        for (auto& user_dto: users_dto)
        {
            auto user = UserOatpp::createShared();

            user->id = user_dto.get_id();
            user->full_name = user_dto.get_full_name();         
            user->login = user_dto.get_login();
            user->city = user_dto.get_city();
            user->access = user_dto.get_access();
       
            users->users->push_back(user);
        }
       
        return createDtoResponse(Status::CODE_200, users);
    }  

    ADD_CORS(posts)
    ENDPOINT_INFO(posts) 
    {
        info->summary = "Get all posts";
        info->addResponse<Object<PostsOatpp>>(Status::CODE_200, "application/json");
        info->tags.push_back("Guest");
    }
    ENDPOINT("GET", "api/v1/posts", posts) 
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();
        std::vector<PostDTO> posts_dto = guest_controller->get_posts();

        auto posts = PostsOatpp::createShared();
        posts->posts = {};

        for (auto& post_dto: posts_dto)
        {
            auto post = PostOatpp::createShared();
            
            post->id = post_dto.get_id();
            post->name = post_dto.get_name(); 

            auto author_dto = post_dto.get_author();
            post->author = UserOatpp::createShared();
            post->author->id = author_dto.get_id();
            post->author->full_name = author_dto.get_full_name();         
            post->author->login = author_dto.get_login();
            post->author->city = author_dto.get_city();
            post->author->access = author_dto.get_access();
 
            post->information = post_dto.get_information();
            post->city = post_dto.get_city();
            post->date = post_dto.get_date();
       
            posts->posts->push_back(post);
        }
       
        return createDtoResponse(Status::CODE_200, posts);
    }  

    ADD_CORS(user_by_id)
    ENDPOINT_INFO(user_by_id) 
    {
        info->summary = "Get user by id";
        info->addResponse<Object<UserOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not user with such id");
        info->tags.push_back("Guest");
    }
    ENDPOINT("GET", "api/v1/users/{id}", user_by_id, PATH(UInt32, id)) 
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();
        UserDTO user_dto = guest_controller->get_user(id);
        if (user_dto)
        {
            auto user = UserOatpp::createShared();
            user->id = user_dto.get_id();
            user->full_name = user_dto.get_full_name();         
            user->login = user_dto.get_login();
            user->city = user_dto.get_city();
            user->access = user_dto.get_access();
            return createDtoResponse(Status::CODE_200, user);
        }

        return createResponse(Status::CODE_404, "ERROR");
    }


    ADD_CORS(post_by_id)
    ENDPOINT_INFO(post_by_id) 
    {
        info->summary = "Get post by id";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not post with such id");
        info->tags.push_back("Guest");
    }
    ENDPOINT("GET", "api/v1/posts/{id}", post_by_id, PATH(UInt32, id)) 
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();
        PostDTO post_dto = guest_controller->get_post(id);
        if (post_dto)
        {
            auto post = PostOatpp::createShared();
            
            post->id = post_dto.get_id();
            post->name = post_dto.get_name(); 

            auto author_dto = post_dto.get_author();
            post->author = UserOatpp::createShared();
            post->author->id = author_dto.get_id();
            post->author->full_name = author_dto.get_full_name();         
            post->author->login = author_dto.get_login();
            post->author->city = author_dto.get_city();
            post->author->access = author_dto.get_access();
 
            post->information = post_dto.get_information();
            post->city = post_dto.get_city();
            post->date = post_dto.get_date();
       
            return createDtoResponse(Status::CODE_200, post);
        }

        return createResponse(Status::CODE_404, "ERROR");
    }


    ADD_CORS(sign_up)
    ENDPOINT_INFO(sign_up) 
    {
        info->summary = "User registration";
        info->addResponse<Object<UserOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Some field is empty or access is not 'C' or 'A'");
        info->addResponse<String>(Status::CODE_502, "text/plain", "There is user with such login");
        info->tags.push_back("Guest");
    }
    ENDPOINT("POST", "/api/v1/users/register", sign_up, BODY_DTO(Object<NewUserOatpp>, user))
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
            auto user = UserOatpp::createShared();
            user->id = user_dto.get_id();
            user->full_name = user_dto.get_full_name();         
            user->login = user_dto.get_login();
            user->city = user_dto.get_city();
            user->access = user_dto.get_access();
            return createDtoResponse(Status::CODE_200, user);
        }

        return createResponse(Status::CODE_502, "ERROR");
    }
};

#include OATPP_CODEGEN_END(ApiController)  // =====================================================
