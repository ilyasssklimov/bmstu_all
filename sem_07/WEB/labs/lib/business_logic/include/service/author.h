#pragma once

#include "client.h"


class AuthorService: public ClientService
{
public:
    explicit AuthorService(std::shared_ptr<IPostRepository> post_repo, 
                           std::shared_ptr<ICommentRepository> comment_repo,
                           std::shared_ptr<IUserRepository>user_repo):
        ClientService(post_repo, comment_repo, user_repo) {};

    PostBL create_post(int user_id, const std::string &name, const std::string &info, const std::string &city,
                       const std::string &organizer,  const std::string &date);
};
