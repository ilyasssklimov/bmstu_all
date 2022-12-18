#include "locator.hpp"
#include "logger.h"
#include "exception.h"
#include "controller/guest.hpp"


GuestController::GuestController()
{
    _guest_service = ServiceLocator::resolve<GuestService>();

    if (!_guest_service)
    {
        log_error("There are not repositories for GuestController");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }
}


std::vector<UserDTO> GuestController::get_users()
{
    std::vector<UserBL> users_bl = _guest_service->get_users();
    log_info("Get all users from GuestController");

    std::vector<UserDTO> users_dto;
    for (auto& user_bl: users_bl)
    {
        int user_id = _guest_service->get_user_id(user_bl);
        users_dto.push_back(UserDTO(user_id, user_bl));
    }
    
    return users_dto;
}


std::vector<PostDTO> GuestController::get_posts()
{
    std::vector<PostBL> posts_bl = _guest_service->get_posts();
    log_info("Get all posts from GuestController");

    std::vector<PostDTO> posts_dto;
    for (auto& post_bl: posts_bl)
    {
        int post_id = _guest_service->get_post_id(post_bl);
        int author_id = post_bl.get_author_id();
        UserBL author_bl = _guest_service->get_user(author_id);
        posts_dto.push_back(PostDTO(post_id, UserDTO(author_id, author_bl), post_bl));
    }
    
    return posts_dto;
}


UserDTO GuestController::get_user(int user_id)
{
    UserBL user_bl = _guest_service->get_user(user_id);
    if (user_bl)
    {
        log_info("Get user from GuestController with id = " + std::to_string(user_id));
        return UserDTO(user_id, user_bl);
    }
    return {};
}

PostDTO GuestController::get_post(int post_id)
{
    PostBL post_bl = _guest_service->get_post(post_id);

    if (post_bl && post_bl.get_visible())
    {
        int author_id = post_bl.get_author_id();
        UserBL author_bl = _guest_service->get_user(author_id);
        log_info("Get post from GuestController with id = " + std::to_string(post_id));
        return PostDTO(post_id, UserDTO(author_id, author_bl), post_bl);
    }

    return {};
}


UserDTO GuestController::sign_up(const std::string &name, const std::string &surname,
                                 const std::string &login, const std::string &password, 
                                 const std::string &city, const std::string &access)
{
    UserBL user_bl = _guest_service->sign_up(name, surname, login, password, city, access);
    if (user_bl)
    {
        int user_id = _guest_service->get_user_id(user_bl);
        log_info("Success registration of user from GuestController with login = " + login);

        return UserDTO(user_id, user_bl);
    }
    return {};
}
