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
