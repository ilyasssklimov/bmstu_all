#pragma once

#include "client.h"


class AuthorService: public ClientService
{
public:
    explicit AuthorService(std::shared_ptr<IPostRepository> post_repo, 
                           std::shared_ptr<ICommentRepository> comment_repo,
                           std::shared_ptr<IUserRepository>user_repo):
        ClientService(post_repo, comment_repo, user_repo) {};
    explicit AuthorService(): ClientService() {}

    PostBL create_post(int user_id, const std::string &name, const std::string &info, const std::string &city,
                       const std::string &organizer,  const std::string &date);
    PostBL delete_post(int post_id);
    PostBL update_post(int post_id, std::string name, std::string information, std::string city, std::string date);
};
