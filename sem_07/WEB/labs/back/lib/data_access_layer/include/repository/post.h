#pragma once

#include <memory>
#include "database/database.h"
#include "irepository/post.h"


class PostRepository: public IPostRepository
{
public:
    explicit PostRepository(std::shared_ptr<IDataBase> db): _db(db) {};
    explicit PostRepository();

    PostBL get_post(int post_id) override;
    int get_post_id(PostBL post) override;
    std::vector<PostBL> get_posts() override;
    std::vector<PostBL> get_posts(const std::string& date, const std::string& name,
                                  const std::string& city, const std::string& author) override;
    std::vector<PostBL> get_unvisible_posts() override;
    PostBL add_post(std::string name, int author_id, std::string information, std::string city,
                    std::string organizer, std::string date) override;
    PostBL delete_post(int post_id) override;
    PostBL update_post(int post_id, std::string name, std::string information,
                       std::string city, std::string date) override;
    PostBL update_post(int post_id, bool visible) override;

private:
    std::shared_ptr<IDataBase> _db;
    static PostBL post_to_post_bl(Post post);
};
