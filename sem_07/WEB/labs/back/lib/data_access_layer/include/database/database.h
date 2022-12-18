#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include "model_dal/user.h"
#include "model_dal/comment.h"


class IDataBase
{
public:
    virtual std::vector<User> get_users() = 0;
    virtual User get_user(int user_id) = 0;
    virtual int get_user_id(const std::string &login) = 0;
    virtual int get_user_id(const std::string &login, const std::string &password) = 0;
    virtual User get_user(const std::string &login, const std::string &password) = 0;
    virtual User add_user(std::string name, std::string surname, std::string login,
                          std::string password, std::string city, std::string access) = 0;
    virtual User delete_user(int user_id) = 0;
    virtual User update_user(int user_id, const std::string& name, const std::string& surname, const std::string& login,
                             const std::string& password, const std::string& city) = 0;
    virtual User update_user(User user, const std::string &name, std::string surname, std::string login,
                             const std::string &password, const std::string &city) = 0;

    virtual std::vector<Post> get_posts() = 0;
    virtual std::vector<Post> get_unvisible_posts() = 0;
    virtual Post get_post(int post_id) = 0;
    virtual int get_post_id(Post post) = 0;
    virtual std::vector<Post> get_posts(const std::string& date, const std::string& name,
                                        const std::string& city, int author) = 0;
    virtual Post add_post(std::string name, int author_id, std::string information, std::string city,
                          std::string organizer, std::string date) = 0;
    virtual Post delete_post(int post_id) = 0;
    virtual Post update_post(int post_id, std::string name, std::string information,
                             std::string city, std::string date, bool visible) = 0;

    virtual Comment get_comment(int comment_id) = 0;
    virtual int get_comment_id(Comment comment) = 0;
    virtual std::vector<Comment> get_comments(int post_id) = 0;
    virtual Comment add_comment(std::string date, std::string text, int author_id, int post_id) = 0;
    virtual Comment delete_comment(int comment_id) = 0;
    virtual Comment update_comment(int comment_id, std::string date, std::string text) = 0;
};
