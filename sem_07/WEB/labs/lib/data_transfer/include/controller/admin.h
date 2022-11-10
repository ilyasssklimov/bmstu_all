#pragma once 

#include "controller/author.h"
#include "service/admin.h"


class AdminController: public AuthorController
{
public:
    explicit AdminController(std::shared_ptr<AdminService> service): AuthorController(), _admin_service(service) {};
    explicit AdminController();

    PostDTO submit_post(int post_id);
    std::vector<PostDTO> get_waiting_posts();

    UserDTO delete_user(int user_id);
    PostDTO delete_post(int post_id);
    CommentDTO delete_comment(int comment_id);

protected:
    std::shared_ptr<AdminService> _admin_service;
};
