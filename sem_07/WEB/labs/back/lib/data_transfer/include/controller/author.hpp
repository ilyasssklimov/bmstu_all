#pragma once 

#include "controller/client.hpp"
#include "service/author.h"


class AuthorController: public ClientController
{
public:
    explicit AuthorController(std::shared_ptr<AuthorService> service): ClientController(), _author_service(service) {};
    explicit AuthorController();

    FullPostDTO create_post(int user_id, const std::string &name, const std::string &info, const std::string &city,
                            const std::string &organizer,  const std::string &date);
    FullPostDTO delete_post(int user_id, int post_id);
    FullPostDTO update_post(int user_id, int post_id, const std::string& name, const std::string& info, 
                            const std::string& city, const std::string& date);

protected:
    std::shared_ptr<AuthorService> _author_service;
};


#include OATPP_CODEGEN_BEGIN(ApiController)

class OatppAuthorController: public oatpp::web::server::api::ApiController 
{
public:
    OatppAuthorController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)): 
        oatpp::web::server::api::ApiController(objectMapper) {}


    // Add post
    ADD_CORS(add_post)
    ENDPOINT_INFO(add_post) 
    {
        info->summary = "Add new post";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Invalid data");
        info->addResponse<String>(Status::CODE_403, "text/plain", "The access should be 'A' or 'M'");
        info->tags.push_back("Post");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("POST", "/api/v1/posts", add_post, BODY_DTO(Object<NewPostOatpp>, post),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>()))
    {
        int user_id = auth->id;
        std::string access = auth->access;

        if (access != "A" && access != "M")
            return createResponse(Status::CODE_403, "ERROR");

        auto author_controller = ServiceLocator::resolve<AuthorController>();
        std::string name = post->name;
        std::string information = post->information;
        std::string city = post->city;
        std::string organizer = post->organizer;

        const time_t tm = time(nullptr);
        char date[64];
        strftime(date, std::size(date), "%d.%m.%Y", localtime(&tm));

        FullPostDTO post_dto = author_controller->create_post(user_id, name, information, city, organizer, date);
        std::cout << post_dto.get_organizer();
        if (post_dto)
            return createDtoResponse(Status::CODE_200, post_dto.get_oatpp_object());

        return createResponse(Status::CODE_400, "ERROR");
    }


    // Update post by id
    ADD_CORS(update_post, "*", "GET,POST,OPTIONS,PATCH")
    ENDPOINT_INFO(update_post) 
    {
        info->summary = "Update post by id";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Unable to update user");
        info->addResponse<String>(Status::CODE_403, "text/plain", "It is not your post");
        info->tags.push_back("Post");
        info->addSecurityRequirement("JWT-auth");
    }
    ENDPOINT("PATCH", "/api/v1/posts/{id}", update_post, PATH(UInt32, id), BODY_DTO(Object<UpdPostOatpp>, user),
             AUTHORIZATION(std::shared_ptr<BearerAuthObject>, auth, ServiceLocator::resolve<BearerAuthHandler>()))
    {
        int user_id = auth->id;
        std::string access = auth->access;

        if (access != "A" && access != "M")
            return createResponse(Status::CODE_403, "ERROR");

        auto author_controller = ServiceLocator::resolve<AuthorController>();
        std::string name = user->name;
        std::string information = user->information;
        std::string city = user->city;
        std::string date = user->date;
        
        FullPostDTO post_dto = author_controller->update_post(user_id, id, name, information, city, date);

        if (post_dto)
            return createDtoResponse(Status::CODE_200, post_dto.get_oatpp_object());

        return createResponse(Status::CODE_403, "ERROR");
    }  
};

#include OATPP_CODEGEN_END(ApiController)
