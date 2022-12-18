#include "locator.hpp"
#include "logger.h"
#include "exception.h"
#include "controller/author.hpp"


AuthorController::AuthorController(): ClientController()
{
    _author_service = ServiceLocator::resolve<AuthorService>();

    if (!_author_service)
    {
        log_error("There are not repositories for AuthorController");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }
}


FullPostDTO AuthorController::create_post(int user_id, const std::string &name, const std::string &info, 
                                      const std::string &city, const std::string &organizer,  const std::string &date)
{
    PostBL post_bl = _author_service->create_post(user_id, name, info, city, organizer, date);

    if (post_bl)
    {
        int post_id = _guest_service->get_post_id(post_bl);
        int author_id = post_bl.get_author_id();
        UserBL author_bl = _guest_service->get_user(author_id);
        log_info("Add post from AuthorController with id = " + std::to_string(post_id));
        return FullPostDTO(post_id, UserDTO(author_id, author_bl), post_bl, {});
    }

    return {};
}
    

FullPostDTO AuthorController::delete_post(int user_id, int post_id)
{    
    PostBL post_bl = _author_service->get_post(post_id);
    std::vector<CommentBL> comments_bl = _client_service->get_comments(post_id);

    std::vector<CommentDTO> comments_dto;
    for (auto& comment_bl: comments_bl)
    {
        int comment_id = _client_service->get_comment_id(comment_bl);
        int comment_author_id = comment_bl.get_author_id();
        UserBL comment_author_bl = _guest_service->get_user(comment_author_id);
        comments_dto.push_back(CommentDTO(comment_id, comment_bl, UserDTO(comment_author_id, comment_author_bl)));
    }

    if (post_bl && user_id == post_bl.get_author_id() && (post_bl = _author_service->delete_post(post_id)))
    {
        int post_author_id = post_bl.get_author_id();
        UserBL post_author_bl = _guest_service->get_user(post_author_id);
        log_info("Delete post from AuthorController with id = " + std::to_string(post_id));
        return FullPostDTO(post_id, UserDTO(post_author_id, post_author_bl), post_bl, comments_dto);
    }

    return {};
}


FullPostDTO AuthorController::update_post(int user_id, int post_id, const std::string& name, const std::string& info, 
                                          const std::string& city, const std::string& date)
{   
    PostBL post_bl = _author_service->get_post(post_id);
    std::vector<CommentBL> comments_bl = _client_service->get_comments(post_id);

    std::vector<CommentDTO> comments_dto;
    for (auto& comment_bl: comments_bl)
    {
        int comment_id = _client_service->get_comment_id(comment_bl);
        int comment_author_id = comment_bl.get_author_id();
        UserBL comment_author_bl = _guest_service->get_user(comment_author_id);
        comments_dto.push_back(CommentDTO(comment_id, comment_bl, UserDTO(comment_author_id, comment_author_bl)));
    }

    if (post_bl && user_id == post_bl.get_author_id() && 
        (post_bl = _author_service->update_post(post_id, name, info, city, date)))
    {
        int post_author_id = post_bl.get_author_id();
        UserBL post_author_bl = _author_service->get_user(post_author_id);
        log_info("Update post from AuthorController with id = " + std::to_string(post_id));
        return FullPostDTO(post_id, UserDTO(post_author_id, post_author_bl), post_bl, comments_dto);
    }

    return {};

}
