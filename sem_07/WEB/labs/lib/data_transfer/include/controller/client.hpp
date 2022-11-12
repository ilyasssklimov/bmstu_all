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
    ADD_CORS(posts)
    ENDPOINT_INFO(posts) 
    {
        info->summary = "Get all posts";
        info->addResponse<Object<PostsOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->queryParams["date"].required = false;
        info->queryParams["name"].required = false;
        info->queryParams["city"].required = false;
        info->queryParams["author"].required = false;
        info->queryParams["date"].allowEmptyValue = true;
        info->queryParams["name"].allowEmptyValue = true;
        info->queryParams["city"].allowEmptyValue = true;
        info->queryParams["author"].allowEmptyValue = true;
        info->tags.push_back("Post");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("GET", "/api/v1/posts", posts, QUERY(String, date, "date", ""), QUERY(String, name, "name", ""), 
             QUERY(String, city, "city", ""), QUERY(String, author, "author", ""),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>()))
    {   
        (void) auth;

        auto client_controller = ServiceLocator::resolve<ClientController>();
        std::vector<FullPostDTO> posts_dto;

        if (!date && !name && !city && !author)
            posts_dto = client_controller->get_full_posts();
        else
            posts_dto = client_controller->get_full_posts(date, name, city, author);

        return createDtoResponse(Status::CODE_200, FullPostDTO::get_oatpp_posts(posts_dto));
    }


    // Get post by id
    ADD_CORS(post_by_id)
    ENDPOINT_INFO(post_by_id) 
    {
        info->summary = "Get post by id";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not post with such id");
        info->tags.push_back("Post");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("GET", "/api/v1/posts/{id}", post_by_id, PATH(UInt32, id),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>())) 
    {       
        (void) auth;

        auto client_controller = ServiceLocator::resolve<ClientController>();
        FullPostDTO post_dto = client_controller->get_full_post(id);

        if (post_dto)       
            return createDtoResponse(Status::CODE_200, post_dto.get_oatpp_object());

        return createResponse(Status::CODE_404, "ERROR");
    }


    // Add comment to post by id
    ADD_CORS(add_comment)
    ENDPOINT_INFO(add_comment) 
    {
        info->summary = "Add comment to post by id";
        info->addResponse<Object<CommentOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not post with such id");
        info->tags.push_back("Comment");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("POST", "/api/v1/posts/{id}/comments", add_comment, PATH(UInt32, id),
             BODY_DTO(Object<NewCommentOatpp>, comment),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>()))
    {
        int user_id = auth->id;
        const time_t tm = time(nullptr);
        char date[64];
        strftime(date, std::size(date), "%d.%m.%Y", localtime(&tm));

        auto client_controller = ServiceLocator::resolve<ClientController>();
        CommentDTO comment_dto = client_controller->add_comment(date, comment->text, user_id, id);

        if (comment_dto)
            return createDtoResponse(Status::CODE_200, comment_dto.get_oatpp_object());

        return createResponse(Status::CODE_404, "ERROR");
    }


    // Update user
    ADD_CORS(update_user, "*", "GET,POST,OPTIONS,PATCH")
    ENDPOINT_INFO(update_user) 
    {
        info->summary = "Update user by id";
        info->addResponse<Object<NewUserOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Unable to update user");
        info->addResponse<String>(Status::CODE_403, "text/plain", "It is not your profile");
        info->tags.push_back("User");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("PATCH", "/api/v1/users/{id}", update_user, PATH(UInt32, id),
             BODY_DTO(Object<UpdUserOatpp>, user),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>()))
    {
        if (auth->id != id)
            return createResponse(Status::CODE_401, "ERROR");

        auto client_controller = ServiceLocator::resolve<ClientController>();
        std::string name = user->name;
        std::string surname = user->surname;
        std::string login = user->login;
        std::string password = user->password;
        std::string city = user->city;
        UserDTO user_dto = client_controller->update_user(id, name, surname, login, password, city);

        if (user_dto)
            return createDtoResponse(Status::CODE_200, user_dto.get_oatpp_object());

        return createResponse(Status::CODE_400, "ERROR");
    }
};

#include OATPP_CODEGEN_END(ApiController)
