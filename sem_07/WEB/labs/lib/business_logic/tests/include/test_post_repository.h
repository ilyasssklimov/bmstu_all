#ifndef TEST_POST_REPOSITORY_H
#define TEST_POST_REPOSITORY_H

#include "controller/guest.h"
#include "test_user_repository.h"
#include "logger.h"


class PostRepository: public IPostRepository
{
public:
    PostRepository(std::vector<PostBL> posts): _posts(posts) {}

    PostBL get_post(int post_id) override
    {
        return _posts[post_id];
    }

    int get_post_id(PostBL post) override
    {
        return std::distance(_posts.begin(), std::find(_posts.begin(), _posts.end(), post));
    }

    std::vector<PostBL> get_posts() override
    {
        return _posts;
    }

    // author filtering is not testing
    std::vector<PostBL> get_posts(const std::string& date, const std::string& name,
                                  const std::string& city, const std::string&) override
    {
        std::vector<PostBL> posts;

        for (PostBL post: _posts)
        {
            if (post.get_date() == date || post.get_name() == name || post.get_city() == city)
                posts.push_back(post);
        }

        return posts;
    }

    PostBL add_post(std::string name, int author_id, std::string information, std::string city,
                            std::string organizer, std::string date) override
    {
        PostBL post(name, author_id, information, city, organizer, date, false);
        _posts.push_back(post);
        return post;
    }

    PostBL delete_post(int post_id) override
    {
        PostBL post = _posts[post_id];
        _posts.erase(_posts.begin() + post_id);
        return post;
    }

    PostBL update_post(int post_id, std::string name, std::string information, std::string city,
                       std::string date, bool visible) override
    {
        log_debug("Start updating post with id = " + std::to_string(post_id));
        PostBL post = _posts[post_id];

        std::string upd_name;
        if (!name.empty())
            upd_name = name;
        else
            upd_name = post.get_name();
        log_debug("After get upd name for post with id = " + std::to_string(post_id));

        std::string upd_information;
        if (!information.empty())
            upd_information = information;
        else
            upd_information = post.get_information();

        std::string upd_city;
        if (!city.empty())
            upd_city = city;
        else
            upd_city = post.get_city();

        std::string upd_date;
        if (!date.empty())
            upd_date = date;
        else
            upd_date = post.get_date();

        log_debug("Success get upd params while updating post with id = " + std::to_string(post_id));
        PostBL upd_post(upd_name, post.get_author_id(), upd_information,
                        upd_city, post.get_organizer(), upd_date, visible);

        _posts[post_id] = upd_post;
        return upd_post;
    }

private:
    std::vector<PostBL> _posts;
};


#endif  // TEST_POST_REPOSITORY_H
