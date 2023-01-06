#include "database/pg_database_async.h"
#include "logger.h"


PGPoolConnection::PGPoolConnection(const std::string& params)
{
    std::lock_guard<std::mutex> locker(_mutex);
    for (int i = 0; i < POOL_SIZE; i++)  
        _pool.emplace(std::make_shared<pqxx::lazyconnection>(params.c_str()));
}


std::shared_ptr<pqxx::lazyconnection> PGPoolConnection::get_connection()
{
    std::unique_lock<std::mutex> locker(_mutex);

    while (_pool.empty())
        _condition.wait(locker);

    std::shared_ptr<pqxx::lazyconnection> connection = _pool.front();
    _pool.pop();

    return connection;
}


void PGPoolConnection::free_connection(std::shared_ptr<pqxx::lazyconnection> connection)
{
    std::unique_lock<std::mutex> locker(_mutex);
    _pool.push(connection);
    locker.unlock();

    _condition.notify_one();
}


PGDatabaseAsync::PGDatabaseAsync(const std::string& params)
{
    _pg_pool = std::make_shared<PGPoolConnection>(params);
}


pqxx::result PGDatabaseAsync::execute_query(std::string& query)
{
    std::shared_ptr<pqxx::lazyconnection> connection = _pg_pool->get_connection();
    pqxx::work worker(reinterpret_cast<pqxx::lazyconnection&>(*connection.get()));

    pqxx::result response = worker.exec(query);
    worker.commit();
    _pg_pool->free_connection(connection);
    
    return response;
}


pqxx::result PGDatabaseAsync::execute_query(std::ostringstream& query)
{
    std::string string_query = query.str();
    return execute_query(string_query);
}


std::vector<User> PGDatabaseAsync::get_users()
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user";
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_info("Response of getting all users from async PostgreSQL DB is empty");
        return {};
    }

    log_info("Get all users from async PostgreSQL DB");
    std::vector<User> users;

    for (const auto &user_db : response)
    {
        User user(pqxx::to_string(user_db[1]), pqxx::to_string(user_db[2]),
                  pqxx::to_string(user_db[3]), pqxx::to_string(user_db[4]),
                  pqxx::to_string(user_db[5]), pqxx::to_string(user_db[6]));
        users.push_back(user);
    }

    return users;
}


User PGDatabaseAsync::get_user(int user_id)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user WHERE id = " << user_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_info("Unable to find user from async PostgreSQL DB with id = " + std::to_string(user_id));
        return {};
    }

    log_info("Get user from async PostgreSQL DB with id = " + std::to_string(user_id));

    User user(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]), pqxx::to_string(response[0][6]));
    return user;
}


int PGDatabaseAsync::get_user_id(const std::string& login)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user WHERE login = " << apostrophes(login);
    pqxx::result response = execute_query(query);
 
    if (response.empty())
    {
        log_info("Unable to find user from async PostgreSQL DB with name = " + login);
        return -1;
    }

    log_info("Get id of user from async PostgreSQL DB with name = " + login);

    return std::stoi(pqxx::to_string(response[0][0]));
}


int PGDatabaseAsync::get_user_id(const std::string &login, const std::string &password)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user WHERE login = " << apostrophes(login) 
          << "AND password = " << apostrophes(password);
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_info("Unable to find user from async PostgreSQL DB with login = " + login + 
                 " and password = " + password);
        return -1;
    }

    log_info("Get user from async PostgreSQL DB with login = " + login + " and password = " + password);
    
    return std::stoi(pqxx::to_string(response[0][0]));
}


User PGDatabaseAsync::get_user(const std::string &login, const std::string &password)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user WHERE login = " << apostrophes(login) 
          << "AND password = " << apostrophes(password);
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_info("Unable to find user from async PostgreSQL DB with login = " + login + 
                 " and password = " + password);
        return {};
    }

    log_info("Get user from async PostgreSQL DB with login = " + login + " and password = " + password);
    
    User user(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]), pqxx::to_string(response[0][6]));
    return user;
}


User PGDatabaseAsync::add_user(std::string name, std::string surname, std::string login,
                               std::string password, std::string city, std::string access)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user WHERE login = " << apostrophes(login);
    pqxx::result response = execute_query(query);

    if (!response.empty())
    {
        log_error("Unable to add user to async PostgreSQL DB with login = " + login + " (it already exists)");
        return {};
    }

    query.str("");;
    query << "INSERT INTO " << DBNAME << ".user (name, surname, login, password, city, access) VALUES (" 
          << apostrophes(name) << ", " << apostrophes(surname) << ", " << apostrophes(login) << ", " 
          << apostrophes(password) << ", " << apostrophes(city) << ", " << apostrophes(access) << ")";
    execute_query(query);

    log_info("Add user to async PostgreSQL DB with login = " + login);

    User user(name, surname, login, password, city, access);
    return user;
}


User PGDatabaseAsync::delete_user(int user_id)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user WHERE id = " << user_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to delete user from async PostgreSQL DB with id = " + std::to_string(user_id));
        return {};
    }

    User user(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]), pqxx::to_string(response[0][6]));


    query.str("");
    query << "SELECT * FROM " << DBNAME << ".post WHERE author_id = " << user_id;;
    response = execute_query(query);

    for (const auto &post_db : response)
    {
        int post_id = std::stoi(pqxx::to_string(post_db[0]));
        delete_post(post_id);
    }

    query.str("");
    query << "DELETE FROM " << DBNAME << ".user WHERE id = " << user_id;
    execute_query(query);
    
    log_info("Delete user from async PostgreSQL DB with id = " + std::to_string(user_id));

    return user;
}


User PGDatabaseAsync::update_user(int user_id, const std::string& name, const std::string& surname, 
                                  const std::string& login, const std::string& password, const std::string& city)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user WHERE id = " << user_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to update user from async PostgreSQL DB with id = " + std::to_string(user_id));
        return {};
    }

    User user(name, surname, login, password, city, pqxx::to_string(response[0]["access"]));

    query.str("");
    query << "UPDATE " << DBNAME << ".user SET name = " << apostrophes(name) << ", surname = " 
          << apostrophes(surname) << ", login = " << apostrophes(login) << ", password = "
          << apostrophes(password) << ", city = " << apostrophes(city) << " WHERE id = " << user_id;
    execute_query(query);

    log_info("UPDATE user from async PostgreSQL DB with id = " + std::to_string(user_id));
    return user;
}


User PGDatabaseAsync::update_user(User user, const std::string &name, std::string surname, std::string login,
                                  const std::string &password, const std::string &city)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".user WHERE login = " << apostrophes(user.get_login()) 
          << " and password = " + apostrophes(user.get_password());
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to update user from async PostgreSQL DB with login = " + user.get_login());
        return {};
    }

    User upd_user(name, surname, login, password, city, pqxx::to_string(response[0]["access"]));

    query.str("");
    query << "UPDATE " << DBNAME << ".user SET name = " << apostrophes(name) << ", surname = " 
          << surname << ", login = " + apostrophes(login) << ", password = " << apostrophes(password) 
          << ", city = " + apostrophes(city) << " WHERE login = " + apostrophes(user.get_login()) 
          << " and password = " + apostrophes(user.get_password());
    execute_query(query);

    log_info("UPDATE user from async PostgreSQL DB with login = " + user.get_login());
    return upd_user;
}


void PGDatabaseAsync::delete_users()
{
    std::ostringstream query;
    query << "DELETE FROM " << DBNAME << ".user";
    execute_query(query);
}


std::vector<Post> PGDatabaseAsync::get_posts()
{    
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".post WHERE visible = true";
    pqxx::result response = execute_query(query);

    log_info("Get all posts from async PostgreSQL DB");
    std::vector<Post> posts;

    for (const auto &post_db : response)
    {
        Post post(pqxx::to_string(post_db[1]), std::stoi(pqxx::to_string(post_db[2])),
                  pqxx::to_string(post_db[3]), pqxx::to_string(post_db[4]),
                  pqxx::to_string(post_db[5]), pqxx::to_string(post_db[6]), post_db[7].as<bool>());
        posts.push_back(post);
    }

    return posts;
}


std::vector<Post> PGDatabaseAsync::get_unvisible_posts()
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".post WHERE visible = false";
    pqxx::result response = execute_query(query);

    log_info("Get unvisible posts from async PostgreSQL DB");
    std::vector<Post> posts;

    for (const auto &post_db : response)
    {
        Post post(pqxx::to_string(post_db[1]), std::stoi(pqxx::to_string(post_db[2])),
                  pqxx::to_string(post_db[3]), pqxx::to_string(post_db[4]),
                  pqxx::to_string(post_db[5]), pqxx::to_string(post_db[6]), post_db[7].as<bool>());
        posts.push_back(post);
    }

    return posts;
}


Post PGDatabaseAsync::get_post(int post_id)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".post WHERE id = " << post_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to find post from async PostgreSQL DB with id = " + std::to_string(post_id));
        return {};
    }

    log_info("Get post from async PostgreSQL DB with id = " + std::to_string(post_id));
    Post post(pqxx::to_string(response[0][1]), std::stoi(pqxx::to_string(response[0][2])),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]), pqxx::to_string(response[0][6]), response[0][7].as<bool>());

    return post;
}


int PGDatabaseAsync::get_post_id(Post post)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".post WHERE name = " << apostrophes(post.get_name()) 
          << " AND author_id = " << post.get_author_id() 
          << " AND information = " << apostrophes(post.get_information()) 
          << " AND city = " << apostrophes(post.get_city()) 
          << " AND organizer = " + apostrophes(post.get_organizer()) 
          << " AND date = " << apostrophes(post.get_date());
    pqxx::result response = execute_query(query);
 
    if (response.empty())
    {
        log_error("Unable to find post from async PostgreSQL DB with name = " + post.get_name());
        return -1;
    }

    log_info("Get id of post from async PostgreSQL DB with name = " + post.get_name());
    return std::stoi(pqxx::to_string(response[0][0]));
}


std::vector<Post> PGDatabaseAsync::get_posts(const std::string& date, const std::string& name,
                                             const std::string& city, int author)
{
    std::ostringstream query, conditions;
    query << "SELECT * FROM " << DBNAME << ".post WHERE visible = true";

    if (!date.empty())
        conditions << " AND date = " << apostrophes(date);
    if (!name.empty())
        conditions << " AND name = " << apostrophes(name);
    if (!city.empty())
        conditions << " AND city = " << apostrophes(city);
    if (author != 0)
        conditions << " AND author_id = " << author;

    if (!conditions.str().empty())
        query << conditions.str();

    pqxx::result response = execute_query(query);
    log_info("Get posts with filters from async PostgreSQL DB");
    std::vector<Post> posts;

    for (const auto &post_db : response)
    {
        Post post(pqxx::to_string(post_db[1]), std::stoi(pqxx::to_string(post_db[2])),
                  pqxx::to_string(post_db[3]), pqxx::to_string(post_db[4]),
                  pqxx::to_string(post_db[5]), pqxx::to_string(post_db[6]), post_db[7].as<bool>());
        posts.push_back(post);
    }

    return posts;
}


Post PGDatabaseAsync::add_post(std::string name, int author_id, std::string information, std::string city,
                               std::string organizer, std::string date)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".post WHERE name = " << apostrophes(name);
    pqxx::result response = execute_query(query);

    if (!response.empty())
    {
        log_error("Unable to add post to DB with name = " + name);
        return {};
    }

    query.str("");
    query << "INSERT INTO " << DBNAME << ".post (name, author_id, information, city, organizer, date) VALUES (" 
          << apostrophes(name) << ", " << author_id << ", " + apostrophes(information) << ", " 
          << apostrophes(city) + ", " + apostrophes(organizer) + ", " + apostrophes(date) + ")";
    execute_query(query);
    
    log_info("Add post to async PostgreSQL DB with login = " + name);

    Post post(name, author_id, information, city, organizer, date, false);
    return post;
}


Post PGDatabaseAsync::delete_post(int post_id)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".post WHERE id = " << post_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to delete post from async PostgreSQL DB with id = " + std::to_string(post_id));
        return {};
    }

    std::vector<Comment> comments = get_comments(post_id);
    for (auto& comment: comments)
    {
        int comment_id = get_comment_id(comment);
        delete_comment(comment_id);
    }

    Post post(pqxx::to_string(response[0][1]), std::stoi(pqxx::to_string(response[0][2])),
              pqxx::to_string(response[0][3]), pqxx::to_string(response[0][4]),
              pqxx::to_string(response[0][5]), pqxx::to_string(response[0][6]), response[0][7].as<bool>());

    query.str("");
    query << "DELETE FROM " << DBNAME << ".post WHERE id = " << post_id;
    execute_query(query);

    log_info("Delete post from async PostgreSQL DB with id = " + std::to_string(post_id));
    return post;
}


Post PGDatabaseAsync::update_post(int post_id, std::string name, std::string information,
                                  std::string city, std::string date, bool visible)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".post WHERE id = " << post_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to update post from async PostgreSQL DB with id = " + std::to_string(post_id));
        return {};
    }

    Post post(name, std::stoi(pqxx::to_string(response[0]["author_id"])), information, city, 
              pqxx::to_string(response[0]["organizer"]), date, visible);
    std::string str_visible = visible ? "true" : "false";

    query.str("");
    query << "UPDATE " << DBNAME << ".post SET name = " << apostrophes(name) << ", information = " 
          << apostrophes(information) << ", city = " << apostrophes(city) << ", date = " 
          << apostrophes(date) + ", visible = " + str_visible << " WHERE id = " << post_id;
    execute_query(query);

    log_info("UPDATE post from async PostgreSQL DB with id = " + std::to_string(post_id));
    return post;
}


void PGDatabaseAsync::delete_posts()
{    
    std::ostringstream query;
    query << "DELETE FROM " << DBNAME << ".post";
    execute_query(query);
}


Comment PGDatabaseAsync::get_comment(int comment_id)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".comment WHERE id = " << comment_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to find comment from async PostgreSQL DB with id = " + std::to_string(comment_id));
        return {};
    }

    log_info("Get comment from async PostgreSQL DB with id = " + std::to_string(comment_id));

    Comment comment(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
                    std::stoi(pqxx::to_string(response[0][3])), std::stoi(pqxx::to_string(response[0][4])));
    return comment;
}


int PGDatabaseAsync::get_comment_id(Comment comment)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".comment WHERE date = " << apostrophes(comment.get_date()) 
          << " AND text = " << apostrophes(comment.get_text()) << " AND author_id = " 
          << comment.get_author_id() << " AND post_id = " << comment.get_post_id();
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to find comment from async PostgreSQL DB with text = " + comment.get_text());
        return -1;
    }

    log_info("Get id of comment from async PostgreSQL DB with text = " + comment.get_text());
    return std::stoi(pqxx::to_string(response[0][0]));
}


std::vector<Comment> PGDatabaseAsync::get_comments(int post_id)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".comment WHERE post_id = " << post_id;
    pqxx::result response = execute_query(query);
    
    std::vector<Comment> comments;
    for (const auto &comment_db : response)
    {
        Comment comment(pqxx::to_string(comment_db[1]), pqxx::to_string(comment_db[2]),
                        std::stoi(pqxx::to_string(comment_db[3])), std::stoi(pqxx::to_string(comment_db[4])));
        comments.push_back(comment);
    }

    log_info("Get comments from async PostgreSQL DB with id = " + std::to_string(post_id));
    return comments;
}


Comment PGDatabaseAsync::add_comment(std::string date, std::string text, int author_id, int post_id)
{
    std::ostringstream query;
    query << "INSERT INTO " << DBNAME << ".comment (date, text, author_id, post_id) VALUES (" 
          << apostrophes(date) << ", " << apostrophes(text) << ", " << author_id << ", " << post_id << ")";
    pqxx::result response = execute_query(query);

    log_info("Add comment to async PostgreSQL DB with post_id = " + std::to_string(post_id));

    Comment comment(date, text, author_id, post_id);
    return comment;
}


Comment PGDatabaseAsync::delete_comment(int comment_id)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".comment WHERE id = " << comment_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to delete comment from async PostgreSQL DB with id = " + std::to_string(comment_id));
        return {};
    }

    Comment comment(pqxx::to_string(response[0][1]), pqxx::to_string(response[0][2]),
                    std::stoi(pqxx::to_string(response[0][3])), std::stoi(pqxx::to_string(response[0][4])));

    query.str("");
    query << "DELETE FROM " << DBNAME << ".comment WHERE id = " <<  comment_id;
    execute_query(query);

    log_info("Delete comment from async PostgreSQL DB with id = " + std::to_string(comment_id));
    return comment;
}


Comment PGDatabaseAsync::update_comment(int comment_id, std::string date, std::string text)
{
    std::ostringstream query;
    query << "SELECT * FROM " << DBNAME << ".comment WHERE id = " << comment_id;
    pqxx::result response = execute_query(query);

    if (response.empty())
    {
        log_error("Unable to update comment from async PostgreSQL DB with id = " + std::to_string(comment_id));
        return {};
    }

    Comment comment(date, text, std::stoi(pqxx::to_string(response[0][3])),
                    std::stoi(pqxx::to_string(response[0][4])));

    query.str("");
    query << "UPDATE " << DBNAME << ".comment SET date = " << apostrophes(date) << ", text = " 
          << apostrophes(text) << " WHERE id = " << comment_id;
    execute_query(query);

    
    log_info("UPDATE comment from async PostgreSQL DB with id = " + std::to_string(comment_id));
    return comment;
}


void PGDatabaseAsync::delete_comments()
{
    std::ostringstream query;
    query << "DELETE FROM " << DBNAME << ".comment";
    execute_query(query);
}


void add_user_to_db(std::shared_ptr<PGDatabaseAsync> db, UserBL user)
{
    db->add_user(
        user.get_name(),
        user.get_surname(),
        user.get_login(),
        user.get_password(),
        user.get_city(),
        user.get_access()
    );
}


void add_post_to_db(std::shared_ptr<PGDatabaseAsync> db, PostBL post)
{
    db->add_post(
        post.get_name(),
        post.get_author_id(),
        post.get_information(),
        post.get_city(),
        post.get_organizer(),
        post.get_date()
    );
}


void add_comment_to_db(std::shared_ptr<PGDatabaseAsync> db, CommentBL comment)
{
    db->add_comment(
        comment.get_date(),
        comment.get_text(),
        comment.get_author_id(),
        comment.get_post_id()
    );
}


void do_visible_post(std::shared_ptr<PGDatabaseAsync> db, int post_id, PostBL post)
{
    db->update_post(
        post_id,
        post.get_name(),
        post.get_information(),
        post.get_city(),
        post.get_date(),
        true
    );
}