#pragma once

#include <memory>
#include "service/guest.h"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/Types.hpp"

#include "model_dto/user.h"
#include "model_dto/post.h"

#include "locator.hpp"


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

protected:
    std::shared_ptr<GuestService> _guest_service;
};


#include OATPP_CODEGEN_BEGIN(ApiController)

class OatppGuestController: public oatpp::web::server::api::ApiController 
{
public:
    OatppGuestController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)): 
        oatpp::web::server::api::ApiController(objectMapper) {}


    // Get all users
    ADD_CORS(users)
    ENDPOINT_INFO(users) 
    {
        info->summary = "Get all users";
        info->addResponse<Object<UsersOatpp>>(Status::CODE_200, "application/json");
        info->tags.push_back("User");
    }
    ENDPOINT("GET", "/api/v1/users", users) 
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();
        std::vector<UserDTO> users_dto = guest_controller->get_users();

        return createDtoResponse(Status::CODE_200, UserDTO::get_oatpp_users(users_dto));
    }  


    // Get user by id
    ADD_CORS(user_by_id)
    ENDPOINT_INFO(user_by_id) 
    {
        info->summary = "Get user by id";
        info->addResponse<Object<UserOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not user with such id");
        info->tags.push_back("User");
    }
    ENDPOINT("GET", "/api/v1/users/{id}", user_by_id, PATH(UInt32, id)) 
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();
        UserDTO user_dto = guest_controller->get_user(id);
        if (user_dto)
            return createDtoResponse(Status::CODE_200, user_dto.get_oatpp_object());

        return createResponse(Status::CODE_404, "ERROR");
    }


    // Get all previews
    ADD_CORS(previews)
    ENDPOINT_INFO(previews) 
    {
        info->summary = "Get all previews";
        info->addResponse<Object<PreviewsOatpp>>(Status::CODE_200, "application/json");
        info->tags.push_back("Preview");
    }
    ENDPOINT("GET", "/api/v1/previews", previews) 
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();
        std::vector<PostDTO> posts_dto = guest_controller->get_posts();

        return createDtoResponse(Status::CODE_200, PostDTO::get_oatpp_previews(posts_dto));
    }  


    // Get preview by id
    ADD_CORS(preview_by_id)
    ENDPOINT_INFO(preview_by_id) 
    {
        info->summary = "Get preview by id";
        info->addResponse<Object<PreviewOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not post with such id");
        info->tags.push_back("Preview");
    }
    ENDPOINT("GET", "/api/v1/previews/{id}", preview_by_id, PATH(UInt32, id)) 
    {
        auto guest_controller = ServiceLocator::resolve<GuestController>();
        PostDTO post_dto = guest_controller->get_post(id);
        if (post_dto)
            return createDtoResponse(Status::CODE_200, post_dto.get_oatpp_object());

        return createResponse(Status::CODE_404, "ERROR");
    }
};

#include OATPP_CODEGEN_END(ApiController)
