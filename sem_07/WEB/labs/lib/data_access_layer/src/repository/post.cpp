#include "exception.h"
#include "repository/post.h"
#include "logger.h"
#include "locator.hpp"


PostRepository::PostRepository()
{
    _db = ServiceLocator::resolve<IDataBase>();

    if (!_db)
    {
        log_error("There are not db for PostRepository");
        time_t time_now = time(nullptr);
        throw ServiceLocatorException(__FILE__, __LINE__, ctime(&time_now));
    }
}


PostBL PostRepository::post_to_post_bl(Post post)
{
    PostBL post_bl = PostBL(post.get_name(), post.get_author_id(), post.get_information(),
                            post.get_city(), post.get_organizer(), post.get_date(), post.get_visible());

    return post_bl;
}



PostBL PostRepository::get_post(int post_id)
{
    Post post = _db->get_post(post_id);
    if (!post)
    {
        time_t time_now = time(nullptr);
        throw PostGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(post);
}


int PostRepository::get_post_id(PostBL post)
{
    Post post_dal(post.get_name(), post.get_author_id(), post.get_information(),
                  post.get_city(), post.get_organizer(), post.get_date(), post.get_visible());
    int post_id = _db->get_post_id(post_dal);

    if (post_id == -1)
    {
        time_t time_now = time(nullptr);
        throw PostGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_id;
}


std::vector<PostBL> PostRepository::get_posts()
{
    std::vector<Post> posts = _db->get_posts();
    if (posts.empty())
    {
        time_t time_now = time(nullptr);
        throw PostGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    std::vector<PostBL> posts_bl;
    for (auto &post: posts)
    {
        PostBL post_bl = post_to_post_bl(post);
        posts_bl.push_back(post_bl);
    }

    return posts_bl;
}

std::vector<PostBL> PostRepository::get_unvisible_posts()
{
    std::vector<Post> posts = _db->get_unvisible_posts();
    if (posts.empty())
    {
        time_t time_now = time(nullptr);
        throw PostGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    std::vector<PostBL> posts_bl;
    for (auto &post: posts)
    {
        PostBL post_bl = post_to_post_bl(post);
        posts_bl.push_back(post_bl);
    }

    return posts_bl;
}


std::vector<PostBL> PostRepository::get_posts(const std::string& date, const std::string& name,
                                              const std::string& city, const std::string& author)
{
    int author_id = 0;
    if (!author.empty())
        author_id = _db->get_user_id(author);
    
    std::vector<Post> posts = _db->get_posts(date, name, city, author_id);
    if (posts.empty())
    {
        time_t time_now = time(nullptr);
        throw PostsGetException(__FILE__, __LINE__, ctime(&time_now));
    }

    std::vector<PostBL> posts_bl;
    for (auto &post: posts)
    {
        PostBL post_bl = post_to_post_bl(post);
        posts_bl.push_back(post_bl);
    }

    return posts_bl;
}


PostBL PostRepository::add_post(std::string name, int author_id, std::string information, std::string city,
                                std::string organizer, std::string date)
{
    log_debug("Try to get post with name = " + name);
    Post post = _db->add_post(name, author_id, information, city, organizer, date);

    if (!post)
    {
        log_debug("Error while adding post in db");
        time_t time_now = time(nullptr);
        throw PostAddException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(post);
}


PostBL PostRepository::delete_post(int post_id)
{
    Post post = _db->delete_post(post_id);
    if (!post)
    {
        time_t time_now = time(nullptr);
        throw PostDeleteException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(post);
}


PostBL PostRepository::update_post(int post_id, std::string name, std::string information,
                                   std::string city, std::string date)
{
    PostBL post = get_post(post_id);

    std::string upd_name = name.empty() ? post.get_name() : name;
    std::string upd_information = information.empty() ? post.get_information() : information;
    std::string upd_city = city.empty() ? post.get_city() : city;
    std::string upd_date = date.empty() ? post.get_date() : date;

    Post upd_post = _db->update_post(post_id, upd_name, upd_information, upd_city, upd_date, post.get_visible());

    if (!upd_post)
    {
        time_t time_now = time(nullptr);
        throw PostUpdateException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(upd_post);
}


PostBL PostRepository::update_post(int post_id, bool visible)
{
    PostBL post = get_post(post_id);
    Post upd_post = _db->update_post(post_id, post.get_name(), post.get_information(), 
                                     post.get_city(), post.get_date(), visible);

    if (!upd_post)
    {
        time_t time_now = time(nullptr);
        throw PostUpdateException(__FILE__, __LINE__, ctime(&time_now));
    }

    return post_to_post_bl(upd_post);
}
