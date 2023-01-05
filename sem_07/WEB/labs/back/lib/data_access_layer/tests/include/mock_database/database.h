#include <gmock/gmock.h>
#include "database/database.h"


class MockDatabase: public IDataBase 
{
public:
    MOCK_METHOD(std::vector<User>, get_users, (), (override));   
    MOCK_METHOD(User, get_user, (int user_id), (override));
    MOCK_METHOD(int, get_user_id, (const std::string &login), (override));
    MOCK_METHOD(int, get_user_id, (const std::string &login, const std::string &password), (override));
    MOCK_METHOD(User, get_user, (const std::string &login, const std::string &password), (override));
    MOCK_METHOD(User, add_user, (std::string name, std::string surname, std::string login,
                                std::string password, std::string city, std::string access), (override));
    MOCK_METHOD(User, delete_user, (int user_id), (override));
    MOCK_METHOD(User, update_user, (int user_id, const std::string& name, const std::string& surname, 
    	                            const std::string& login, const std::string& password, const std::string& city), (override));
    MOCK_METHOD(User, update_user, (User user, const std::string &name, std::string surname, std::string login,
                                    const std::string &password, const std::string &city), (override));
    MOCK_METHOD(void, delete_users, (), (override));

    MOCK_METHOD(std::vector<Post>, get_posts, (), (override));
    MOCK_METHOD(std::vector<Post>, get_unvisible_posts, (), (override));
    MOCK_METHOD(Post, get_post, (int post_id), (override));
    MOCK_METHOD(int, get_post_id, (Post post), (override));
    MOCK_METHOD(std::vector<Post>, get_posts, (const std::string& date, const std::string& name,
                                               const std::string& city, int author), (override));
    MOCK_METHOD(Post, add_post, (std::string name, int author_id, std::string information, std::string city,
                                 std::string organizer, std::string date), (override));
    MOCK_METHOD(Post, delete_post, (int post_id), (override));
    MOCK_METHOD(Post, update_post, (int post_id, std::string name, std::string information,
                                    std::string city, std::string date, bool visible), (override));
    MOCK_METHOD(void, delete_posts, (), (override));

    MOCK_METHOD(Comment, get_comment, (int comment_id), (override));
    MOCK_METHOD(int, get_comment_id, (Comment comment), (override));
    MOCK_METHOD(std::vector<Comment>, get_comments, (int post_id), (override));
    MOCK_METHOD(Comment, add_comment, (std::string date, std::string text, int author_id, int post_id), (override));
    MOCK_METHOD(Comment, delete_comment, (int comment_id), (override));
    MOCK_METHOD(Comment, update_comment, (int comment_id, std::string date, std::string text), (override));
    MOCK_METHOD(void, delete_comments, (), (override));
};