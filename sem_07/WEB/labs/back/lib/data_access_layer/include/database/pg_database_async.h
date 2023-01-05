#pragma once

#include "config.h"
#include "database.h"
#include <pqxx/pqxx>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <sstream>


#define POOL_SIZE 10
#define apostrophes(str) ("\'" + str + "\'")


class PGPoolConnection 
{
public:
    explicit PGPoolConnection(const std::string& params);
    std::shared_ptr<pqxx::lazyconnection> get_connection();
    void free_connection(std::shared_ptr<pqxx::lazyconnection> connection);

private:
    std::queue<std::shared_ptr<pqxx::lazyconnection>> _pool;
    std::mutex _mutex;
    std::condition_variable _condition;
};


class PGDatabaseAsync: public IDataBase
{
public:
    explicit PGDatabaseAsync(const std::string& params);

    std::vector<User> get_users() override;
    User get_user(int user_id) override;
    int get_user_id(const std::string &login) override;
    int get_user_id(const std::string &login, const std::string &password) override;
    User get_user(const std::string &login, const std::string &password) override;
    User add_user(std::string name, std::string surname, std::string login,
                  std::string password, std::string city, std::string access) override;
    User delete_user(int user_id) override;
    User update_user(int user_id, const std::string& name, const std::string& surname, const std::string& login,
                     const std::string& password, const std::string& city) override;
    User update_user(User user, const std::string &name, std::string surname, std::string login,
                     const std::string &password, const std::string &city) override;
    void delete_users() override;

    std::vector<Post> get_posts() override;
    std::vector<Post> get_unvisible_posts() override;
    Post get_post(int post_id) override;
    int get_post_id(Post post) override;
    std::vector<Post> get_posts(const std::string& date, const std::string& name,
                                const std::string& city, int author) override;
    Post add_post(std::string name, int author_id, std::string information, std::string city,
                          std::string organizer, std::string data) override;
    Post delete_post(int post_id) override;
    Post update_post(int post_id, std::string name, std::string information,
                     std::string city, std::string data, bool visible) override;
    void delete_posts() override;

    Comment get_comment(int comment_id) override;
    int get_comment_id(Comment comment) override;
    std::vector<Comment> get_comments(int post_id) override;
    Comment add_comment(std::string data, std::string text, int author_id, int post_id) override;
    Comment delete_comment(int comment_id) override;
    Comment update_comment(int comment_id, std::string date, std::string text) override;
    void delete_comments() override;

private:
    std::shared_ptr<PGPoolConnection> _pg_pool;
    pqxx::result execute_query(std::string& query);
    pqxx::result execute_query(std::ostringstream& query);
};


void add_user_to_db(std::shared_ptr<PGDatabaseAsync> db, UserBL user);
void add_post_to_db(std::shared_ptr<PGDatabaseAsync> db, PostBL post);
