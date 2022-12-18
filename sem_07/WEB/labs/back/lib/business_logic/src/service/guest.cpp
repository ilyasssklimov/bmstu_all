#include "service/guest.h"
#include "logger.h"
#include "exception.h"


GuestService::GuestService()
{
    auto post_repo = ServiceLocator::resolve<IPostRepository>();
    auto user_repo = ServiceLocator::resolve<IUserRepository>();

    if (!post_repo || !user_repo)
    {
        log_error("There are not repositories for GuestService");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }

    _post_repo = post_repo;
    _user_repo = user_repo;
}


UserBL GuestService::sign_up(const std::string &name, const std::string &surname, const std::string &login,
                             const std::string &password, const std::string &city, const std::string &access)
{
    try
    {
        UserBL user = _user_repo->add_user(name, surname, login, password, city, access);
        log_info("New user with login \"" + login + "\" registered");
        return user;
    }
    catch (UserAddException &e)
    {
        log_error(e.what());
        log_error("Unable to register user with login \"" + login + "\"");
    }
    catch (...)
    {
        log_error("Some error during registration user with login \"" + login + "\"");
    }

    return {};
}


UserBL GuestService::sign_in(const std::string &login, const std::string &password)
{
    try
    {
        UserBL user = _user_repo->check_user(login, password);
        if (user)
        {
            log_info("User with login \"" + login + "\" successfully logged in");
            return user;
        }
        else
        {
            log_error("User input incorrect login and / or password");
            return {};
        }
    }
    catch (PostsGetException &e)
    {
        log_error(e.what());
        log_error("Unable to get posts while logging in system");
    }
    catch (...)
    {
        log_error("Some error while logging in system");
    }

    return {};
}


std::vector<UserBL> GuestService::get_users()
{
    try
    {
        std::vector<UserBL> user_vector = _user_repo->get_users();
        log_info("Get all users");
        return user_vector;
    }
    catch (UsersGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting all users");
    }

    return {};
}


int GuestService::get_user_id(UserBL user)
{
    try
    {
        int user_id = _user_repo->get_user_id(user);
        log_info("Get user id = " + std::to_string(user_id));
        return user_id;
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting user id");
    }

    return {};
}


UserBL GuestService::get_user(int user_id)
{
    try
    {
        UserBL user = _user_repo->get_user(user_id);
        log_info("Get user with id = " + std::to_string(user_id));
        return user;
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting user");
    }

    return {};
}


UserBL GuestService::get_user(const std::string &login, const std::string &password)
{
    try
    {
        UserBL user = _user_repo->check_user(login, password);
        log_info("Get user with login = " + login);
        return user;
    }
    catch (UserGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting user");
    }

    return {};

}


PostBL GuestService::get_post(int post_id)
{
    try
    {
        PostBL post = _post_repo->get_post(post_id);
        log_info("Get post with title " + post.get_name());
        return post;
    }
    catch (PostGetException &e)
    {
        log_error(e.what());
        log_error("Unable to get post with id = " + std::to_string(post_id) + " while getting post");
    }
    catch (...)
    {
        log_error("Some error while getting post with id " + std::to_string(post_id));
    }

    return {};
}


int GuestService::get_post_id(PostBL post)
{
    try
    {
        int post_id = _post_repo->get_post_id(post);
        log_info("Get post id = " + std::to_string(post_id));
        return post_id;
    }
    catch (PostGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting post id");
    }

    return {};
}


std::vector<PostBL> GuestService::get_posts(std::vector<int> &post_ids)
{
    if (post_ids.empty())
    {
        log_error("Vector of post ids for getting posts is empty");
        return {};
    }

    std::vector<PostBL> post_vector;
    PostBL post;

    log_info("Try to get posts by ids");
    for (int post_id: post_ids)
    {
        post = get_post(post_id);
        if (post)
            post_vector.push_back(post);
    }

    return post_vector;
}


std::vector<PostBL> GuestService::get_posts()
{
    try
    {
        std::vector<PostBL> post_vector = _post_repo->get_posts();
        log_info("Get all posts");
        return post_vector;
    }
    catch (PostsGetException &e)
    {
        log_error(e.what());
    }
    catch (...)
    {
        log_error("Some error while getting all posts");
    }

    return {};
}


std::string GuestService::get_post_info(int post_id)
{
    PostBL post = get_post(post_id);
    if (post)
    {
        log_info("Get information from post with title " + post.get_name());
        return post.get_information();
    }
    else
    {
        log_error("Unable to get post with id = " + std::to_string(post_id) + " while getting post info");
        return "";
    }
}


std::vector<int> GuestService::get_posts_ids(const std::vector<PostBL> &posts)
{
    std::vector<int> posts_ids;
    for (auto &post: posts)
        posts_ids.push_back(_post_repo->get_post_id(post));

    return posts_ids;
}
