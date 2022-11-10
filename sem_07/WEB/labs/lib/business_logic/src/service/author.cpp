#include "service/author.h"
#include "logger.h"
#include "exception.h"


PostBL AuthorService::create_post(int user_id, const std::string &name, const std::string &info, const std::string &city,
                                  const std::string &organizer, const std::string &date)
{
    try
    {
        PostBL post = _post_repo->add_post(name, user_id, info, city, organizer, date);
        log_info("Create post with title \"" + name + "\"");
        return post;
    }
    catch (PostAddException &e)
    {
        log_error(e.what());
        log_error("Unable to add post with title \"" + name + "\"");
    }
    catch (...)
    {
        log_error("Some error while creating post by author with id = " + std::to_string(user_id));
    }

    return {};
}


PostBL AuthorService::delete_post(int post_id)
{
    try
    {
        PostBL post = _post_repo->delete_post(post_id);
        log_info("Delete post with id = " + std::to_string(post_id));
        return post;
    }
    catch (PostDeleteException &e)
    {
        log_error(e.what());
        log_error("Unable to delete post with id = " + std::to_string(post_id));
    }
    catch (...)
    {
        log_error("Some error while deleting post with id = " + std::to_string(post_id));
    }

    return {};  
    
}


PostBL AuthorService::update_post(int post_id, std::string name, std::string information, std::string city, std::string date)
{
    try
    {
        PostBL post = _post_repo->update_post(post_id, name, information, city, date);
        log_info("Update post with id = " + std::to_string(post_id));
        return post;
    }
    catch (PostUpdateException &e)
    {
        log_error(e.what());
        log_error("Unable to update post with id = " + std::to_string(post_id));
    }
    catch (...)
    {
        log_error("Some error while updating post with id = " + std::to_string(post_id));
    }

    return {}; 
}