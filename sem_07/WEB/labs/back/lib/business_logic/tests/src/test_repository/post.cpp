#include <algorithm>
#include "test_repository/post.h"
#include "logger.h"


PostBL TestPostRepository::get_post(int post_id) 
{
    return _posts[post_id];
}


int TestPostRepository::get_post_id(PostBL post)
{
    return std::distance(_posts.begin(), std::find(_posts.begin(), _posts.end(), post));
}


std::vector<PostBL> TestPostRepository::get_posts()
{
    return _posts;
}


std::vector<PostBL> TestPostRepository::get_posts(const std::string& date, const std::string& name,
                                                  const std::string& city, const std::string&)
{
    std::vector<PostBL> posts;

    for (PostBL post: _posts)
    {
        if (post.get_date() == date || post.get_name() == name || post.get_city() == city)
            posts.push_back(post);
    }

    return posts;
}


std::vector<PostBL> TestPostRepository::get_unvisible_posts()
{
    std::vector<PostBL> posts;

    for (PostBL post: _posts)
    {
        if (post.get_visible() == false)
            posts.push_back(post);
    }

    return posts;
}



PostBL TestPostRepository::add_post(std::string name, int author_id, std::string information, std::string city,
                                    std::string organizer, std::string date)
{
    PostBL post(name, author_id, information, city, organizer, date, false);
    _posts.push_back(post);
    return post;
}


PostBL TestPostRepository::delete_post(int post_id)
{
    PostBL post = _posts[post_id];
    _posts.erase(_posts.begin() + post_id);
    return post;
}


PostBL TestPostRepository::update_post(int post_id, std::string name, std::string information, 
                                       std::string city, std::string date)
{
    PostBL post = _posts[post_id];

    std::string upd_name = name.empty() ? post.get_name() : name;
    std::string upd_information = information.empty() ? post.get_information() : information;
    std::string upd_city = city.empty() ? post.get_city() : city;
    std::string upd_date = date.empty() ? post.get_date() : date;

    PostBL upd_post(upd_name, post.get_author_id(), upd_information,
                    upd_city, post.get_organizer(), upd_date, post.get_visible());

    _posts[post_id] = upd_post;
    return upd_post;
}


PostBL TestPostRepository::update_post(int post_id, bool visible)
{
    PostBL post = _posts[post_id];

    PostBL upd_post(post.get_name(), post.get_author_id(), post.get_information(),
                    post.get_city(), post.get_organizer(), post.get_date(), visible);

    _posts[post_id] = upd_post;
    return upd_post;
}
