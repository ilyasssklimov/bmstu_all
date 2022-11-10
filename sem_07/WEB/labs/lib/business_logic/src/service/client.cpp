#include "service/client.h"
#include "logger.h"
#include "exception.h"


ClientService::ClientService(): GuestService()
{
    auto comment_repo = ServiceLocator::resolve<ICommentRepository>();

    if (!comment_repo)
    {
        log_error("There are not repositories for ClientService");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }

    _comment_repo = comment_repo;
}


int ClientService::get_comment_id(CommentBL comment)
{
    try
    {
        int comment_id = _comment_repo->get_comment_id(comment);
        log_info("Get comment id = " + std::to_string(comment_id));
        return comment_id;
    }
    catch (CommentGetException &e)
    {
        log_error(e.what());
    }
    catch (std::exception &e)
    {
        log_error(e.what());
        log_error("Some error while getting comment id");
    }

    return {};
}


CommentBL ClientService::get_comment(int comment_id)
{   
    try
    {
        CommentBL comment = _comment_repo->get_comment(comment_id);
        log_info("Get comment with id = " + std::to_string(comment_id));
        return comment;
    }
    catch (CommentGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting comment");
    }

    return {};

}


CommentBL ClientService::add_comment(const std::string &date, const std::string& text, int author_id, int post_id)
{
    try
    {
        CommentBL comment = _comment_repo->add_comment(date, text, author_id, post_id);
        log_info("Add post with text \"" + comment.get_text() + "\"");
        return comment;
    }
    catch (CommentAddException &e)
    {
        log_error(e.what());
        log_error("Unable to add post with text \"" + text + "\"");
    }
    catch (...)
    {
        log_error("Some error while adding comment with text \"" + text + "\"");
    }

    return {};
}


std::string ClientService::get_organizer(int post_id)
{
    PostBL post = get_post(post_id);
    if (post)
    {
        log_info("Get organizer from post with title " + post.get_name());
        return post.get_organizer();
    }
    else
    {
        log_error("Unable to get post with id = " + std::to_string(post_id) + " while getting post organizer");
        return "";
    }
}


std::vector<PostBL> ClientService::get_posts(const std::string& data="", const std::string& name="",
                                             const std::string& city="", const std::string& author="")
{
    try
    {
        std::vector<PostBL> post_vector = _post_repo->get_posts(data, name, city, author);
        log_info("Get posts with filters");
        return post_vector;
    }
    catch (PostsFilterGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting posts with filters");
    }

    return {};
}


UserBL ClientService::update(int user_id, const std::string& name, const std::string& surname, const std::string& login,
                             const std::string& password, const std::string& city)
{
    try
    {
        UserBL updating_user = _user_repo->update_user(user_id, name, surname, login, password, city);
        log_info("Update user with id = " + std::to_string(user_id));
        return updating_user;
    }
    catch (UserUpdateException &e)
    {
        log_error(e.what());
        log_error("Unable to update user with id = " + std::to_string(user_id));
    }
    catch (...)
    {
        log_error("Some error while updating user with id = " + std::to_string(user_id));
    }

    return {};
}


std::vector<CommentBL> ClientService::get_comments(int post_id)
{
    try
    {
        std::vector<CommentBL> comments = _comment_repo->get_comments(post_id);
        log_info("Get comments with post_id = " + std::to_string(post_id));
        return comments;
    }
    catch (CommentsGetException &e)
    {
        log_error(e.what());
        log_error("Unable to get comments with post_id = " + std::to_string(post_id));
    }
    catch (...)
    {
        log_error("Some error while getting comments with post_id = " + std::to_string(post_id));
    }

    return {};
}
