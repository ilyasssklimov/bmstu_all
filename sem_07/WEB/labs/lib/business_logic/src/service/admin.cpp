#include <algorithm>
#include "service/admin.h"
#include "logger.h"
#include "exception.h"


PostBL AdminService::submit_post(PostBL post)
{
    try
    {
        int post_id = _post_repo->get_post_id(post);
        _post_repo->update_post(post_id, true);

        log_info("Submit post with title \"" + post.get_name() + "\"");
        return post;
    }
    catch (PostGetException &e)
    {
        log_error(e.what());
        log_error("Unable to get post_id with title \"" + post.get_name() + "\"");
    }
    catch (PostUpdateException &e)
    {
        log_error(e.what());
        log_error("Unable to update post with title \"" + post.get_name() + "\"");
    }
    catch (...)
    {
        log_error("Some error while submitting post");
    }

    return {};
}


PostBL AdminService::submit_post(int post_id)
{
    try
    {
        PostBL post = _post_repo->update_post(post_id, true);

        log_info("Submit post with id " + std::to_string(post_id));
        return post;
    }
    catch (PostGetException &e)
    {
        log_error(e.what());
        log_error("Unable to get post_id with id " + std::to_string(post_id));
    }
    catch (PostUpdateException &e)
    {
        log_error(e.what());
        log_error("Unable to update post with id " + std::to_string(post_id));
    }
    catch (...)
    {
        log_error("Some error while submitting post");
    }

    return {};
}


std::vector<PostBL> AdminService::get_waiting_posts()
{
    try
    {
        std::vector<PostBL> posts = _post_repo->get_unvisible_posts();
        log_info("Get all waiting posts");
        return posts;
    }
    catch (PostsGetException &e)
    {
        log_info(e.what());
        log_info("Unable to get waiting posts");
    }
    catch (...)
    {
        log_error("Some error while getting  post");
    }

    return {};
}


UserBL AdminService::delete_user(int user_id)
{
    try
    {
        UserBL user = _user_repo->get_user(user_id);
        _user_repo->delete_user(user_id);
        log_info("Delete user with id " + std::to_string(user_id));

        return user;
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
        log_error("Unable to find user with id " + std::to_string(user_id) + " while deleting user");
    }
    catch (UserDeleteException &e)
    {
        log_error(e.what());
        log_error("Unable to delete user with id " + std::to_string(user_id));
    }
    catch (...)
    {
        log_error("Some error while deleting user");
    }

    return {};
}


PostBL AdminService::delete_post(int post_id)
{
    try
    {
        PostBL post = _post_repo->get_post(post_id);
        _post_repo->delete_post(post_id);
        log_info("Delete post with id " + std::to_string(post_id));

        return post;
    }
    catch (PostGetException &e)
    {
        log_error(e.what());
        log_error("Unable to find post with id " + std::to_string(post_id) + " while deleting post");
    }
    catch (PostDeleteException &e)
    {
        log_error(e.what());
        log_error("Unable to delete post with id " + std::to_string(post_id));
    }
    catch (...)
    {
        log_error("Some error while deleting post");
    }

    return {};
}


CommentBL AdminService::delete_comment(int comment_id)
{
    try
    {
        CommentBL comment = _comment_repo->get_comment(comment_id);
        _comment_repo->delete_comment(comment_id);
        log_info("Delete comment with id " + std::to_string(comment_id));

        return comment;
    }
    catch (CommentGetException &e)
    {
        log_error(e.what());
        log_error("Unable to find comment with id " + std::to_string(comment_id) + " while deleting comment");
    }
    catch (UserDeleteException &e)
    {
        log_error(e.what());
        log_error("Unable to delete comment with id " + std::to_string(comment_id));
    }
    catch (...)
    {
        log_error("Some error while deleting comment");
    }

    return {};
}
