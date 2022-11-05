#include <algorithm>
#include "service/admin.h"
#include "logger.h"
#include "exception.h"


PostBL AdminService::submit_post(PostBL post)
{
    try
    {
        int post_id = _post_repo->get_post_id(post);
        _post_repo->update_post(post_id, "", "", "", "", true);

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


std::vector<PostBL> AdminService::get_waiting_posts()
{
    return _post_repo->get_unvisible_posts();
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
