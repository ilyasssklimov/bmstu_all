#pragma once

#include "client.h"


class AdminService: public ClientService
{
public:
    explicit AdminService(std::shared_ptr<IPostRepository> post_repo, 
                          std::shared_ptr<ICommentRepository> comment_repo,
                          std::shared_ptr<IUserRepository> user_repo):
        ClientService(post_repo, comment_repo, user_repo) {};

    PostBL submit_post(PostBL post);
    std::vector<PostBL> get_waiting_posts();
    UserBL delete_user(int user_id);
};
