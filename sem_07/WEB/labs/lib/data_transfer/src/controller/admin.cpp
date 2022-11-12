#include "locator.hpp"
#include "logger.h"
#include "exception.h"
#include "controller/admin.hpp"


AdminController::AdminController(): AuthorController()
{
    _admin_service = ServiceLocator::resolve<AdminService>();

    if (!_admin_service)
    {
        log_error("There are not repositories for AdminController");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }
}


FullPostDTO AdminController::submit_post(int post_id)
{
    PostBL post_bl = _admin_service->submit_post(post_id);

    if (post_bl)
    {
        int author_id = post_bl.get_author_id();
        UserBL author_bl = _guest_service->get_user(author_id);
        log_info("Submit post from AdminController with id = " + std::to_string(post_id));
        return FullPostDTO(post_id, UserDTO(author_id, author_bl), post_bl, {});
    }

    return {};

}


std::vector<FullPostDTO> AdminController::get_waiting_posts()
{
    std::vector<PostBL> posts_bl = _admin_service->get_waiting_posts();
    log_info("Get waiting posts from AdminController");

    std::vector<FullPostDTO> posts_dto;
    for (auto& post_bl: posts_bl)
    {
        int post_id = _guest_service->get_post_id(post_bl);
        int author_id = post_bl.get_author_id();
        UserBL author_bl = _guest_service->get_user(author_id);
        posts_dto.push_back(FullPostDTO(post_id, UserDTO(author_id, author_bl), post_bl, {}));
    }
    
    return posts_dto;
}


UserDTO AdminController::delete_user(int user_id)
{    
    UserBL user_bl = _admin_service->get_user(user_id);

    if (user_bl && (user_bl = _admin_service->delete_user(user_id)))
    {
        log_info("Delete user from AdminController with id = " + std::to_string(user_id));
        return UserDTO(user_id, user_bl);
    }

    return {};

}


FullPostDTO AdminController::delete_post(int post_id)
{    
    PostBL post_bl = _admin_service->get_post(post_id);
    std::vector<CommentBL> comments_bl = _client_service->get_comments(post_id);

    std::vector<CommentDTO> comments_dto;
    for (auto& comment_bl: comments_bl)
    {
        int comment_id = _client_service->get_comment_id(comment_bl);
        int comment_author_id = comment_bl.get_author_id();
        UserBL comment_author_bl = _guest_service->get_user(comment_author_id);
        comments_dto.push_back(CommentDTO(comment_id, comment_bl, UserDTO(comment_author_id, comment_author_bl)));
    }

    if (post_bl && (post_bl = _admin_service->delete_post(post_id)))
    {
        int post_author_id = post_bl.get_author_id();
        UserBL post_author_bl = _admin_service->get_user(post_author_id);
        log_info("Delete post from AdminController with id = " + std::to_string(post_id));
        return FullPostDTO(post_id, UserDTO(post_author_id, post_author_bl), post_bl, comments_dto);
    }

    return {};
}


CommentDTO AdminController::delete_comment(int comment_id)
{
    CommentBL comment_bl = _admin_service->get_comment(comment_id);

    if (comment_bl && (comment_bl = _admin_service->delete_comment(comment_id)))
    {
        int author_id = comment_bl.get_author_id();
        UserBL author_bl = _admin_service->get_user(author_id);
        log_info("Delete comment from AdminController with id = " + std::to_string(comment_id));
        return CommentDTO(comment_id, comment_bl, UserDTO(author_id, author_bl));
    }

    return {};

}