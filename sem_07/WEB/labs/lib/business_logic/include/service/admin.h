#pragma once

#include "author.h"


class AdminService: public AuthorService
{
public:
    explicit AdminService(std::shared_ptr<IPostRepository> post_repo, 
                          std::shared_ptr<ICommentRepository> comment_repo,
                          std::shared_ptr<IUserRepository> user_repo):
        AuthorService(post_repo, comment_repo, user_repo) {};
    explicit AdminService(): AuthorService() {}

    PostBL submit_post(PostBL post);
    PostBL submit_post(int post_id);
    std::vector<PostBL> get_waiting_posts();

    UserBL delete_user(int user_id);
    PostBL delete_post(int post_id);
    CommentBL delete_comment(int comment_id);
};
