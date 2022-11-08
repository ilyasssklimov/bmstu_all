#pragma once 

#include "controller/guest.h"
#include "service/client.h"


class ClientController: public GuestController
{
public:
    explicit ClientController(std::shared_ptr<ClientService> service): GuestController(), _client_service(service) {};
    explicit ClientController();

    std::vector<FullPostDTO> get_full_posts();
    FullPostDTO get_full_post(int post_id);
    std::vector<FullPostDTO> get_posts(const std::string& date, const std::string& name,
                                       const std::string& city, const std::string& author);

    CommentDTO add_comment(const std::string& date, const std::string& text, int author_id, int post_id);
    UserDTO update(int user_id, const std::string& name, const std::string& surname, const std::string& login,
                  const std::string& password, const std::string& city);

protected:
    std::shared_ptr<ClientService> _client_service;
};
