#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include "locator.hpp"
#include "controller/auth.h"
#include "controller/guest.h"
#include "controller/client.h"
#include "controller/author.h"


#include OATPP_CODEGEN_BEGIN(ApiController)  // ===================================================

class OatppController: public oatpp::web::server::api::ApiController 
{
public:
    OatppController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}

    ADD_CORS(users)
    ENDPOINT_INFO(users) 
    {
        info->summary = "Get all users";
        info->addResponse<Object<UsersOatpp>>(Status::CODE_200, "application/json");
        info->tags.push_back("Guest");
    }
    ENDPOINT("GET", "/api/v1/users", users) 
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
    ENDPOINT("GET", "/api/v1/posts", posts) 
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
    ENDPOINT("GET", "/api/v1/users/{id}", user_by_id, PATH(UInt32, id)) 
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


    ADD_CORS(full_posts)
    ENDPOINT_INFO(full_posts) 
    {
        info->summary = "Get all full posts";
        info->addResponse<Object<FullPostsOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->tags.push_back("Client");
    }
    ENDPOINT("GET", "/api/v1/posts/full", full_posts, QUERY(String, token)) 
    {   
        if (!ServiceLocator::resolve<AuthController>()->verify_token(token->c_str()))
            return createResponse(Status::CODE_401, "ERROR");

        auto client_controller = ServiceLocator::resolve<ClientController>();
        std::vector<FullPostDTO> posts_dto = client_controller->get_full_posts();

        auto posts = FullPostsOatpp::createShared();
        posts->posts = {};

        for (auto& post_dto: posts_dto)
        {
            auto post = FullPostOatpp::createShared();
            
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
            post->organizer = post_dto.get_organizer();
            post->city = post_dto.get_city();
            post->date = post_dto.get_date();
            
            post->comments = {}; 
            for (auto& comment_dto: post_dto.get_comments())
            {
                auto comment = CommentOatpp::createShared();    
                comment->date = comment_dto.get_date();
                comment->text = comment_dto.get_text();

                auto comment_author_dto = comment_dto.get_author();
                comment->author = UserOatpp::createShared();
                comment->author->id = comment_author_dto.get_id();
                comment->author->full_name = comment_author_dto.get_full_name(); 
                comment->author->login = comment_author_dto.get_login();
                comment->author->city = comment_author_dto.get_city();
                comment->author->access = comment_author_dto.get_access();

                post->comments->push_back(comment);
            }

            posts->posts->push_back(post);
        }

        return createDtoResponse(Status::CODE_200, posts);
    }

    
    ADD_CORS(full_posts_filters)
    ENDPOINT_INFO(full_posts_filters) 
    {
        info->summary = "Get all full posts with filters";
        info->addResponse<Object<FullPostsOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->queryParams["date"].required = false;
        info->queryParams["name"].required = false;
        info->queryParams["city"].required = false;
        info->queryParams["author"].required = false;
        info->queryParams["date"].allowEmptyValue = true;
        info->queryParams["name"].allowEmptyValue = true;
        info->queryParams["city"].allowEmptyValue = true;
        info->queryParams["author"].allowEmptyValue = true;
        info->tags.push_back("Client");
    }
    ENDPOINT("GET", "/api/v1/posts/full/filters", full_posts_filters, QUERY(String, token), 
             QUERY(String, date, "date", ""), QUERY(String, name, "name", ""), 
             QUERY(String, city, "city", ""), QUERY(String, author, "author", "")) 
    {   
        if (!ServiceLocator::resolve<AuthController>()->verify_token(token->c_str()))
            return createResponse(Status::CODE_401, "ERROR");

        auto client_controller = ServiceLocator::resolve<ClientController>();
        std::vector<FullPostDTO> posts_dto = client_controller->get_full_posts(date->c_str(), name->c_str(), 
                                                                               city->c_str(), author->c_str());
        auto posts = FullPostsOatpp::createShared();
        posts->posts = {};

        for (auto& post_dto: posts_dto)
        {
            auto post = FullPostOatpp::createShared();
            
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
            post->organizer = post_dto.get_organizer();
            post->city = post_dto.get_city();
            post->date = post_dto.get_date();
            
            post->comments = {}; 
            for (auto& comment_dto: post_dto.get_comments())
            {
                auto comment = CommentOatpp::createShared();    
                comment->date = comment_dto.get_date();
                comment->text = comment_dto.get_text();

                auto comment_author_dto = comment_dto.get_author();
                comment->author = UserOatpp::createShared();
                comment->author->id = comment_author_dto.get_id();
                comment->author->full_name = comment_author_dto.get_full_name(); 
                comment->author->login = comment_author_dto.get_login();
                comment->author->city = comment_author_dto.get_city();
                comment->author->access = comment_author_dto.get_access();

                post->comments->push_back(comment);
            }

            posts->posts->push_back(post);
        }

        return createDtoResponse(Status::CODE_200, posts);
    }


    ADD_CORS(full_post_by_id)
    ENDPOINT_INFO(full_post_by_id) 
    {
        info->summary = "Get full post by id";
        info->addResponse<Object<FullPostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not post with such id");
        info->tags.push_back("Client");
    }
    ENDPOINT("GET", "/api/v1/posts/full/{id}", full_post_by_id, PATH(UInt32, id), QUERY(String, token)) 
    {
        if (!ServiceLocator::resolve<AuthController>()->verify_token(token->c_str()))
            return createResponse(Status::CODE_401, "ERROR");

        auto client_controller = ServiceLocator::resolve<ClientController>();
        FullPostDTO post_dto = client_controller->get_full_post(id);

        if (post_dto)
        {
            auto post = FullPostOatpp::createShared();
            
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
            post->organizer = post_dto.get_organizer();
            post->city = post_dto.get_city();
            post->date = post_dto.get_date();
            
            post->comments = {}; 
            for (auto& comment_dto: post_dto.get_comments())
            {
                auto comment = CommentOatpp::createShared();    
                comment->date = comment_dto.get_date();
                comment->text = comment_dto.get_text();

                auto comment_author_dto = comment_dto.get_author();
                comment->author = UserOatpp::createShared();
                comment->author->id = comment_author_dto.get_id();
                comment->author->full_name = comment_author_dto.get_full_name(); 
                comment->author->login = comment_author_dto.get_login();
                comment->author->city = comment_author_dto.get_city();
                comment->author->access = comment_author_dto.get_access();

                post->comments->push_back(comment);
            }

            return createDtoResponse(Status::CODE_200, post);
        }

        return createResponse(Status::CODE_404, "ERROR");
    }


    ADD_CORS(add_comment)
    ENDPOINT_INFO(add_comment) 
    {
        info->summary = "Add comment to post by id";
        info->addResponse<Object<CommentOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not post with such id");
        info->tags.push_back("Client");
    }
    ENDPOINT("POST", "/api/v1/posts/full/{id}/comments", add_comment, PATH(UInt32, id), QUERY(String, token), 
             BODY_DTO(Object<NewCommentOatpp>, comment))
    {
        if (!ServiceLocator::resolve<AuthController>()->verify_token(token->c_str()))
            return createResponse(Status::CODE_401, "ERROR");

        int user_id = ServiceLocator::resolve<AuthController>()->get_id(token->c_str());
        const time_t tm = time(nullptr);
        char date[64];
        strftime(date, std::size(date), "%d.%m.%Y", localtime(&tm));

        auto client_controller = ServiceLocator::resolve<ClientController>();
        CommentDTO comment_dto = client_controller->add_comment(date, comment->text, user_id, id);

        if (comment_dto)
        {
            auto new_comment = CommentOatpp::createShared();

            new_comment->date = date;
            new_comment->text = comment->text; 

            auto author_dto = comment_dto.get_author();
            new_comment->author = UserOatpp::createShared();
            new_comment->author->id = author_dto.get_id();
            new_comment->author->full_name = author_dto.get_full_name(); 
            new_comment->author->login = author_dto.get_login();
            new_comment->author->city = author_dto.get_city();
            new_comment->author->access = author_dto.get_access();

            return createDtoResponse(Status::CODE_200, new_comment);
        }

        return createResponse(Status::CODE_404, "ERROR");
    }


    ADD_CORS(update_user, "*", "GET,POST,OPTIONS,PATCH")
    ENDPOINT_INFO(update_user) 
    {
        info->summary = "Update user by id";
        info->addResponse<Object<NewUserOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Unable to update user");
        info->addResponse<String>(Status::CODE_403, "text/plain", "It is not your profile");
        info->tags.push_back("Client");
    }
    ENDPOINT("PATCH", "/api/v1/users/{id}", update_user, PATH(UInt32, id), QUERY(String, token), 
             BODY_DTO(Object<UpdUserOatpp>, user))
    {
        if (!ServiceLocator::resolve<AuthController>()->verify_token(token->c_str()))
            return createResponse(Status::CODE_401, "ERROR");

        size_t user_id = ServiceLocator::resolve<AuthController>()->get_id(token->c_str());
        if (user_id != id)
            return createResponse(Status::CODE_401, "ERROR");

        auto client_controller = ServiceLocator::resolve<ClientController>();
        std::string name = user->name;
        std::string surname = user->surname;
        std::string login = user->login;
        std::string password = user->password;
        std::string city = user->city;
        UserDTO user_dto = client_controller->update_user(user_id, name, surname, login, password, city);

        if (user_dto)
        {
            auto upd_user = NewUserOatpp::createShared();

            upd_user->name = name;
            upd_user->surname = surname;
            upd_user->login = login;
            upd_user->password = password;
            upd_user->city = city;
            upd_user->access = user_dto.get_access();

            return createDtoResponse(Status::CODE_200, upd_user);
        }

        return createResponse(Status::CODE_400, "ERROR");
    }


    ADD_CORS(post_by_id)
    ENDPOINT_INFO(post_by_id) 
    {
        info->summary = "Get post by id";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_404, "text/plain", "There is not post with such id");
        info->tags.push_back("Guest");
    }
    ENDPOINT("GET", "/api/v1/posts/{id}", post_by_id, PATH(UInt32, id)) 
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


    ADD_CORS(add_post)
    ENDPOINT_INFO(add_post) 
    {
        info->summary = "Add new post";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Invalid data");
        info->addResponse<String>(Status::CODE_403, "text/plain", "The access should be 'A' or 'M'");
        info->tags.push_back("Author");
    }
    ENDPOINT("POST", "/api/v1/posts", add_post, QUERY(String, token), BODY_DTO(Object<NewPostOatpp>, post))
    {
        if (!ServiceLocator::resolve<AuthController>()->verify_token(token->c_str()))
            return createResponse(Status::CODE_401, "ERROR");

        int user_id = ServiceLocator::resolve<AuthController>()->get_id(token->c_str());
        std::string access = ServiceLocator::resolve<AuthController>()->get_access(user_id);

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

        PostDTO post_dto = author_controller->create_post(user_id, name, information, city, organizer, date);

        if (post_dto)
        {
            auto post = PostOatpp::createShared();
            
            post->id = post_dto.get_id();
            post->name = name; 

            auto author_dto = post_dto.get_author();
            post->author = UserOatpp::createShared();
            post->author->id = author_dto.get_id();
            post->author->full_name = author_dto.get_full_name();         
            post->author->login = author_dto.get_login();
            post->author->city = author_dto.get_city();
            post->author->access = author_dto.get_access();
 
            post->information = information;
            post->city = city;
            post->date = date;
       
            return createDtoResponse(Status::CODE_200, post);
        }

        return createResponse(Status::CODE_400, "ERROR");
    }


    ADD_CORS(delete_post, "*", "GET,POST,OPTIONS,DELETE")
    ENDPOINT_INFO(delete_post) 
    {
        info->summary = "Delete post";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Invalid data");
        info->addResponse<String>(Status::CODE_403, "text/plain", "The access should be 'A' or 'M' and post should be yours");
        info->tags.push_back("Author");
    }
    ENDPOINT("DELETE", "/api/v1/posts/{id}", delete_post, PATH(UInt32, id), QUERY(String, token))
    {
        if (!ServiceLocator::resolve<AuthController>()->verify_token(token->c_str()))
            return createResponse(Status::CODE_401, "ERROR");

        int user_id = ServiceLocator::resolve<AuthController>()->get_id(token->c_str());
        std::string access = ServiceLocator::resolve<AuthController>()->get_access(user_id);

        if (access != "A" && access != "M")
            return createResponse(Status::CODE_403, "ERROR");

        auto author_controller = ServiceLocator::resolve<AuthorController>();
        PostDTO post_dto = author_controller->delete_post(user_id, id);

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

        return createResponse(Status::CODE_403, "ERROR");
    }


    ADD_CORS(update_post, "*", "GET,POST,OPTIONS,PATCH")
    ENDPOINT_INFO(update_post) 
    {
        info->summary = "Update post by id";
        info->addResponse<Object<PostOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_401, "text/plain", "Invalid token");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Unable to update user");
        info->addResponse<String>(Status::CODE_403, "text/plain", "It is not your post");
        info->tags.push_back("Author");
    }
    ENDPOINT("PATCH", "/api/v1/posts/{id}", update_post, PATH(UInt32, id), QUERY(String, token), 
             BODY_DTO(Object<UpdPostOatpp>, user))
    {
        if (!ServiceLocator::resolve<AuthController>()->verify_token(token->c_str()))
            return createResponse(Status::CODE_401, "ERROR");

        int user_id = ServiceLocator::resolve<AuthController>()->get_id(token->c_str());
        std::string access = ServiceLocator::resolve<AuthController>()->get_access(user_id);

        if (access != "A" && access != "M")
            return createResponse(Status::CODE_403, "ERROR");

        auto author_controller = ServiceLocator::resolve<AuthorController>();

        std::string name = user->name;
        std::string information = user->information;
        std::string city = user->city;
        std::string date = user->date;
        
        PostDTO post_dto = author_controller->update_post(user_id, id, name, information, city, date);

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

        return createResponse(Status::CODE_403, "ERROR");
    }


    ADD_CORS(sign_up)
    ENDPOINT_INFO(sign_up) 
    {
        info->summary = "User registration";
        info->addResponse<Object<AuthOatpp>>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_400, "text/plain", "Some field is empty or access is not 'C' or 'A'");
        info->addResponse<String>(Status::CODE_502, "text/plain", "There is user with such login");
        info->tags.push_back("Guest");
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
        info->tags.push_back("Guest");
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

#include OATPP_CODEGEN_END(ApiController)  // =====================================================
