#pragma once

#include <memory>
#include "service/guest.h"

#include "model_dto/user.h"
#include "model_dto/post.h"
#include "model_dto/oatpp.hpp"


class GuestController
{
public:
    explicit GuestController(std::shared_ptr<GuestService> service): _guest_service(service) {};
    explicit GuestController();
    
    std::vector<UserDTO> get_users();
    std::vector<PostDTO> get_posts();
    UserDTO get_user(int user_id);
    PostDTO get_post(int post_id);

    UserDTO sign_up(const std::string& name, const std::string& surname, const std::string& login,
                    const std::string& password, const std::string& city, const std::string& access);

protected:
    std::shared_ptr<GuestService> _guest_service;
};
