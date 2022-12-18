#include <gtest/gtest.h>
#include "controller/author.h"
#include "test_user_repository.h"
#include "test_post_repository.h"
#include "test_comment_repository.h"



TEST(CONTROLLER_AUTHOR_TEST, CREATE_POST)
{
    UserBL user_1("name_1", "surname_1", "login_1", "password_1", "city_1", "C", {});
    UserBL user_2("name_2", "surname_2", "login_2", "password_2", "city_2", "M", {});
    std::vector<UserBL> users = { user_1, user_2 };
    UserRepository user_repo(users);

    std::string organizer_1 = "organizer_1";
    std::string organizer_2 = "organizer_2";
    PostBL post_1("name_1", 0, "info_1", "city_1", organizer_1, "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", organizer_2, "date_2", false);
    std::vector<PostBL> posts = { post_1, post_2 };
    PostRepository post_repo(posts);

    CommentBL comment_1("date_1", "text_1", 0, 0);
    CommentBL comment_2("date_2", "text_2", 1, 0);
    std::vector<CommentBL> comments = { comment_1, comment_2 };
    CommentRepository comment_repo(comments);

    AuthorController author_controller(0, &post_repo, &comment_repo, &user_repo);

    std::string name_3 = "name_3";
    std::string info_3 = "info_3";
    std::string city_3 = "city_3";
    std::string organizer_3 = "organizer_3";
    std::string date_3 = "date_3";
    PostBL post_3(name_3, 0, info_3, city_3, organizer_3, date_3, false);

    PostBL creating_post = author_controller.create_post(name_3, info_3, city_3, organizer_3, date_3);

    EXPECT_EQ(creating_post, post_3);
    EXPECT_EQ(user_repo.get_user(1).get_posts().size(), 1);
    EXPECT_EQ(user_repo.get_user(1).get_posts()[0], post_3);
}
