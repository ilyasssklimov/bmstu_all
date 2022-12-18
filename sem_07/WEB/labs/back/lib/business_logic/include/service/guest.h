#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "model_bl/post.h"
#include "model_bl/user.h"
#include "irepository/post.h"
#include "irepository/user.h"
#include "irepository/comment.h"
#include "locator.hpp"


class GuestService
{
public:
    explicit GuestService(std::shared_ptr<IPostRepository> post_repo, std::shared_ptr<IUserRepository> user_repo):
        _post_repo(post_repo), _user_repo(user_repo) {}
    explicit GuestService();

    UserBL sign_up(const std::string &name, const std::string &surname, const std::string &login,
                   const std::string &password, const std::string &city, const std::string &access);
    UserBL sign_in(const std::string &login, const std::string &password);

    std::vector<UserBL> get_users();
    int get_user_id(UserBL user);
    UserBL get_user(int user_id);
    UserBL get_user(const std::string &login, const std::string &password);

    std::vector<PostBL> get_posts();
    int get_post_id(PostBL post);
    PostBL get_post(int post_id);
    
    std::vector<PostBL> get_posts(std::vector<int> &post_ids);
    std::vector<int> get_posts_ids(const std::vector<PostBL>& posts);
    std::string get_post_info(int post_id);

protected:
    std::shared_ptr<IPostRepository> _post_repo;
    std::shared_ptr<IUserRepository> _user_repo;
};
