#pragma once

#include "guest.h"
#include "irepository/comment.h"
#include "irepository/user.h"


class ClientService: public GuestService
{
public:
    explicit ClientService(std::shared_ptr<IPostRepository> post_repo,
                           std::shared_ptr<ICommentRepository> comment_repo,
                           std::shared_ptr<IUserRepository> user_repo):
        GuestService(post_repo, user_repo), _comment_repo(comment_repo) {};

    CommentBL add_comment(const std::string& date, const std::string& text, int author_id, int post_id);
    std::string get_organizer(int post_id);
    std::vector<PostBL> get_posts(const std::string& date, const std::string& name,
                                  const std::string& city, const std::string& author);
    UserBL update(int user_id, const std::string& name, const std::string& surname, const std::string& login,
                  const std::string& password, const std::string& city);
    std::vector<CommentBL> get_comments(int post_id);

protected:
    std::shared_ptr<ICommentRepository> _comment_repo;
};
