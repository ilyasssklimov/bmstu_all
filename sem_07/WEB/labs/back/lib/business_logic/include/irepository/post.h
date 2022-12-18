#pragma once

#include "model_bl/post.h"


class IPostRepository
{
public:
    virtual PostBL get_post(int post_id) = 0;
    virtual int get_post_id(PostBL post) = 0;
    virtual std::vector<PostBL> get_posts() = 0;
    virtual std::vector<PostBL> get_posts(const std::string& date, const std::string& name,
                                          const std::string& city, const std::string& author) = 0;
    virtual std::vector<PostBL> get_unvisible_posts() = 0;
    virtual PostBL add_post(std::string name, int author_id, std::string information, std::string city,
                            std::string organizer, std::string date) = 0;
    virtual PostBL delete_post(int post_id) = 0;
    virtual PostBL update_post(int post_id, std::string name, std::string information,
                               std::string city, std::string date) = 0;
    virtual PostBL update_post(int post_id, bool visible) = 0;
};
