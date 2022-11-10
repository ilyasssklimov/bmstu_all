#pragma once 

#include "controller/client.h"
#include "service/author.h"


class AuthorController: public ClientController
{
public:
    explicit AuthorController(std::shared_ptr<AuthorService> service): ClientController(), _author_service(service) {};
    explicit AuthorController();

    PostDTO create_post(int user_id, const std::string &name, const std::string &info, const std::string &city,
                        const std::string &organizer,  const std::string &date);
    PostDTO delete_post(int user_id, int post_id);
    PostDTO update_post(int user_id, int post_id, const std::string& name, const std::string& info, 
                        const std::string& city, const std::string& date);

protected:
    std::shared_ptr<AuthorService> _author_service;
};
