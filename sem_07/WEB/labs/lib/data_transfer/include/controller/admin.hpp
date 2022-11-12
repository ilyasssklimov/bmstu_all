#pragma once 

#include "controller/author.hpp"
#include "service/admin.h"


class AdminController: public AuthorController
{
public:
    explicit AdminController(std::shared_ptr<AdminService> service): AuthorController(), _admin_service(service) {};
    explicit AdminController();

    FullPostDTO submit_post(int post_id);
    std::vector<FullPostDTO> get_waiting_posts();

    UserDTO delete_user(int user_id);
    FullPostDTO delete_post(int post_id);
    CommentDTO delete_comment(int comment_id);

protected:
    std::shared_ptr<AdminService> _admin_service;
};


#include OATPP_CODEGEN_BEGIN(ApiController)

class OatppAdminController: public oatpp::web::server::api::ApiController 
{
public:
    OatppAdminController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)): 
        oatpp::web::server::api::ApiController(objectMapper) {}


    // Get waiting posts
    ADD_CORS(waiting_posts)
    ENDPOINT_INFO(waiting_posts) 
    {
        info->summary = "Get all waiting posts";
        info->addResponse<Object<PreviewsOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_403, "text/plain", "You should be admin");
        info->tags.push_back("Post");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("GET", "/api/v1/posts/waiting", waiting_posts,
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>())) 
    {
        std::string access = auth->access;

        if (access != "M")
            return createResponse(Status::CODE_403, "ERROR");

        auto admin_controller = ServiceLocator::resolve<AdminController>();
        std::vector<FullPostDTO> posts_dto = admin_controller->get_waiting_posts();

        return createDtoResponse(Status::CODE_200, FullPostDTO::get_oatpp_posts(posts_dto));
    } 

 
    // Submit post
    ADD_CORS(submit_post, "*", "GET,POST,OPTIONS,PATCH")
    ENDPOINT_INFO(submit_post) 
    {
        info->summary = "Submit post by id";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_404, "text/plain", "Unable to find post as waiting");
        info->addResponse<String>(Status::CODE_403, "text/plain", "You should be admin");
        info->tags.push_back("Post");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("PATCH", "/api/v1/posts/waiting/{id}", submit_post, PATH(UInt32, id),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>())) 
    {    
        std::string access = auth->access;

        if (access != "M")
            return createResponse(Status::CODE_403, "ERROR");

        auto admin_controller = ServiceLocator::resolve<AdminController>();
        FullPostDTO post_dto = admin_controller->submit_post(id);
        if (post_dto)
            return createDtoResponse(Status::CODE_200, post_dto.get_oatpp_object());

        return createResponse(Status::CODE_404, "ERROR");
    }

    
    ADD_CORS(delete_user, "*", "GET,POST,OPTIONS,DELETE")
    ENDPOINT_INFO(delete_user) 
    {
        info->summary = "Delete user by id";
        info->addResponse<Object<UserOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Invalid data");
        info->addResponse<String>(Status::CODE_403, "text/plain", "The access should be 'M'");
        info->tags.push_back("User");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("DELETE", "/api/v1/users/{id}", delete_user, PATH(UInt32, id),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>())) 
    {
        std::string access = auth->access;
        std::cout << "ACCESS = " << access << std::endl;
        if (access != "M")
            return createResponse(Status::CODE_403, "ERROR");

        UserDTO user_dto = ServiceLocator::resolve<AdminController>()->delete_user(id);

        if (user_dto)
            return createDtoResponse(Status::CODE_200, user_dto.get_oatpp_object());

        return createResponse(Status::CODE_400, "ERROR");
    }


    // Delete post by id
    ADD_CORS(delete_post, "*", "GET,POST,OPTIONS,DELETE")
    ENDPOINT_INFO(delete_post) 
    {
        info->summary = "Delete post by id";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Invalid data");
        info->addResponse<String>(Status::CODE_403, "text/plain", "The access should be 'A' or 'M' and if 'A' post should be yours");
        info->tags.push_back("Post");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("DELETE", "/api/v1/posts/{id}", delete_post, PATH(UInt32, id),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>()))
    {
        int user_id = auth->id;
        std::string access = auth->access;

        FullPostDTO post_dto;
        if (access == "A")
            post_dto = ServiceLocator::resolve<AuthorController>()->delete_post(user_id, id);
        else if (access == "M")
            post_dto = ServiceLocator::resolve<AdminController>()->delete_post(id);
        else
            return createResponse(Status::CODE_403, "ERROR");

        if (post_dto)
            return createDtoResponse(Status::CODE_200, post_dto.get_oatpp_object());

        return createResponse(Status::CODE_403, "ERROR");
    }
    

    // Delete comment by id
    ADD_CORS(delete_comment, "*", "GET,POST,OPTIONS,DELETE")
    ENDPOINT_INFO(delete_comment) 
    {
        info->summary = "Delete comment by id";
        info->addResponse<Object<PreviewOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Invalid data");
        info->addResponse<String>(Status::CODE_403, "text/plain", "The access should be 'M'");
        info->tags.push_back("Comment");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("DELETE", "/api/v1/posts/{post_id}/comments/{comment_id}", delete_comment, 
             PATH(UInt32, post_id), PATH(UInt32, comment_id),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>()))
    {
        std::string access = auth->access;

        if (access != "M")
            return createResponse(Status::CODE_403, "ERROR");

        auto admin_controller = ServiceLocator::resolve<AdminController>();
        if (post_id != (size_t) admin_controller->get_comment(comment_id).get_post_id())
            return createResponse(Status::CODE_400, "ERROR");

        CommentDTO comment_dto = admin_controller->delete_comment(comment_id);
        if (comment_dto)
            return createDtoResponse(Status::CODE_200, comment_dto.get_oatpp_object());

        return createResponse(Status::CODE_403, "ERROR");
    }
};

#include OATPP_CODEGEN_END(ApiController)
