#include "locator.hpp"
#include "logger.h"
#include "exception.h"
#include "controller/client.h"


ClientController::ClientController(): GuestController()
{
    _client_service = ServiceLocator::resolve<ClientService>();

    if (!_client_service)
    {
        log_error("There are not repositories for ClientController");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }
}


std::vector<FullPostDTO> ClientController::get_full_posts()
{
    std::vector<PostBL> posts_bl = _guest_service->get_posts();
    log_info("Get all posts from ClientController");

    std::vector<FullPostDTO> posts_dto;
    for (auto& post_bl: posts_bl)
    {
        int post_id = _guest_service->get_post_id(post_bl);
        int post_author_id = post_bl.get_author_id();
        UserBL post_author_bl = _guest_service->get_user(post_author_id);

        std::vector<CommentBL> comments_bl = _client_service->get_comments(post_id);
        std::vector<CommentDTO> comments_dto;
        for (auto& comment_bl: comments_bl)
        {
            int comment_author_id = comment_bl.get_author_id();
            UserBL comment_author_bl = _guest_service->get_user(comment_author_id);
            comments_dto.push_back(CommentDTO(comment_bl, UserDTO(comment_author_id, comment_author_bl)));
        }

        posts_dto.push_back(FullPostDTO(post_id, UserDTO(post_author_id, post_author_bl), post_bl, comments_dto));
    }

    return posts_dto;
}


FullPostDTO ClientController::get_full_post(int post_id)
{
    PostBL post_bl = _guest_service->get_post(post_id);

    if (post_bl)
    {
        int post_author_id = post_bl.get_author_id();
        UserBL post_author_bl = _guest_service->get_user(post_author_id);

        std::vector<CommentBL> comments_bl = _client_service->get_comments(post_id);
        std::vector<CommentDTO> comments_dto;
        for (auto& comment_bl: comments_bl)
        {
            int comment_author_id = comment_bl.get_author_id();
            UserBL comment_author_bl = _guest_service->get_user(comment_author_id);
            comments_dto.push_back(CommentDTO(comment_bl, UserDTO(comment_author_id, comment_author_bl)));
        }

        log_info("Get post from ClientController with id = " + std::to_string(post_id));
        return FullPostDTO(post_id, UserDTO(post_author_id, post_author_bl), post_bl, comments_dto);
    }

    return {};
}


std::vector<FullPostDTO> ClientController::get_full_posts(const std::string& date, const std::string& name,
                                                          const std::string& city, const std::string& author)
{ 
    std::vector<PostBL> posts_bl = _client_service->get_posts(date, name, city, author);
    log_info("Get all posts with filters from ClientController");

    std::vector<FullPostDTO> posts_dto;
    for (auto& post_bl: posts_bl)
    {
        int post_id = _guest_service->get_post_id(post_bl);
        int post_author_id = post_bl.get_author_id();
        UserBL post_author_bl = _guest_service->get_user(post_author_id);

        std::vector<CommentBL> comments_bl = _client_service->get_comments(post_id);
        std::vector<CommentDTO> comments_dto;
        for (auto& comment_bl: comments_bl)
        {
            int comment_author_id = comment_bl.get_author_id();
            UserBL comment_author_bl = _guest_service->get_user(comment_author_id);
            comments_dto.push_back(CommentDTO(comment_bl, UserDTO(comment_author_id, comment_author_bl)));
        }

        posts_dto.push_back(FullPostDTO(post_id, UserDTO(post_author_id, post_author_bl), post_bl, comments_dto));
    }

    return posts_dto;
}


CommentDTO ClientController::add_comment(const std::string& date, const std::string& text, int author_id, int post_id)
{
    CommentBL comment_bl = _client_service->add_comment(date, text, author_id, post_id);
    if (comment_bl)
    {
        UserBL user_bl = _guest_service->get_user(author_id);
        log_info("Success adding of comment from ClientController (author_id = " + std::to_string(author_id) + ")");

        return CommentDTO(comment_bl, UserDTO(author_id, user_bl));
    }
    return {};
}
