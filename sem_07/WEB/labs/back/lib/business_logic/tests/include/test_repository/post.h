#pragma once

#include <algorithm>
#include "service/guest.h"


class PostRepository: public IPostRepository
{
public:
    PostRepository(std::vector<PostBL> posts): _posts(posts) {}

    PostBL get_post(int post_id) override;
    int get_post_id(PostBL post) override;

    std::vector<PostBL> get_posts() override;
    std::vector<PostBL> get_posts(const std::string& date, const std::string& name,
                                  const std::string& city, const std::string&) override;
    
    std::vector<PostBL> get_unvisible_posts() override;

    PostBL add_post(std::string name, int author_id, std::string information, std::string city,
                            std::string organizer, std::string date) override;
    PostBL delete_post(int post_id) override;

    PostBL update_post(int post_id, std::string name, std::string information, std::string city,
                       std::string date) override;
    PostBL update_post(int post_id, bool visible) override;

private:
    std::vector<PostBL> _posts;
};

