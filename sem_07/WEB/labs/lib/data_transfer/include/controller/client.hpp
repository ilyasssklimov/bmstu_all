#pragma once 

#include "controller/auth.hpp"
#include "controller/guest.hpp"
#include "service/client.h"
#include "model_dto/auth.h"


class ClientController: public GuestController
{
public:
    explicit ClientController(std::shared_ptr<ClientService> service): GuestController(), _client_service(service) {};
    explicit ClientController();

    std::vector<FullPostDTO> get_full_posts();
    FullPostDTO get_full_post(int post_id);
    std::vector<FullPostDTO> get_full_posts(const std::string& date, const std::string& name,
                                            const std::string& city, const std::string& author);

    CommentDTO add_comment(const std::string& date, const std::string& text, int author_id, int post_id);
    UserDTO update_user(int user_id, const std::string& name, const std::string& surname, const std::string& login,
                        const std::string& password, const std::string& city);

    CommentDTO get_comment(int comment_id);

protected:
    std::shared_ptr<ClientService> _client_service;
};


#include OATPP_CODEGEN_BEGIN(ApiController)

class OatppClientController: public oatpp::web::server::api::ApiController 
{
public:
    OatppClientController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)): 
        oatpp::web::server::api::ApiController(objectMapper) {}


    // Get all posts    
    ENDPOINT_INFO(posts) 
    {
        info->summary = "Get all posts";
        info->addResponse<Object<PostsOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->tags.push_back("Post");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("GET", "/api/v1/posts", posts, 
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>()))
    {   
        (void) auth;

        auto client_controller = ServiceLocator::resolve<ClientController>();
        std::vector<FullPostDTO> posts_dto = client_controller->get_full_posts();

        return createDtoResponse(Status::CODE_200, FullPostDTO::get_oatpp_posts(posts_dto));
    }
};

#include OATPP_CODEGEN_END(ApiController)
