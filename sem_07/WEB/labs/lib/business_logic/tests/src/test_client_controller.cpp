#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "test_user_repository.h"
#include "test_post_repository.h"
#include "test_comment_repository.h"


TEST(CONTROLLER_CLIENT_TEST, ADD_COMMENT)
{
    UserBL user_1("name_1", "surname_1", "login_1", "password_1", "city_1", "C", {});
    UserBL user_2("name_2", "surname_2", "login_2", "password_2", "city_2", "C", {});
    std::vector<UserBL> users = { user_1, user_2 };
    UserRepository user_repo(users);

    PostBL post_1("name_1", 0, "info_1", "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", "organizer_2", "date_2", false);
    std::vector<PostBL> posts = { post_1, post_2 };
    PostRepository post_repo(posts);

    CommentBL comment_1("date_1", "text_1", 0, 0);
    CommentBL comment_2("date_2", "text_2", 1, 0);
    std::vector<CommentBL> comments = { comment_1, comment_2 };
    CommentRepository comment_repo(comments);

    std::string date_3 = "date_3";
    std::string text_3 = "text_3";
    int author_id_3 = 1;
    int post_id_3 = 1;
    CommentBL comment_3(date_3, text_3, author_id_3, post_id_3);

    ClientController client_controller(0, &post_repo, &comment_repo, &user_repo);
    CommentBL adding_comment = client_controller.add_comment(date_3, text_3, author_id_3, post_id_3);

    EXPECT_EQ(adding_comment, comment_3);
    EXPECT_EQ(adding_comment, comment_repo.get_comment(2));
}


TEST(CONTROLLER_CLIENT_TEST, GET_POST_ORGANIZER)
{
    UserBL user_1("name_1", "surname_1", "login_1", "password_1", "city_1", "C", {});
    UserBL user_2("name_2", "surname_2", "login_2", "password_2", "city_2", "C", {});
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

    ClientController client_controller(0, &post_repo, &comment_repo, &user_repo);
    std::string getting_organizer_1 = client_controller.get_organizer(0);
    std::string getting_organizer_2 = client_controller.get_organizer(1);

    EXPECT_EQ(getting_organizer_1, organizer_1);
    EXPECT_EQ(getting_organizer_2, organizer_2);
}


TEST(CONTROLLER_CLIENT_TEST, GET_POSTS_BY_FILTERS)
{
    UserBL user_1("name_1", "surname_1", "login_1", "password_1", "city_1", "C", {});
    UserBL user_2("name_2", "surname_2", "login_2", "password_2", "city_2", "C", {});
    std::vector<UserBL> users = { user_1, user_2 };
    UserRepository user_repo(users);

    PostBL post_1("name_1", 0, "info_1", "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", "organizer_2", "date_2", false);
    std::vector<PostBL> posts = { post_1, post_2 };
    PostRepository post_repo(posts);

    CommentBL comment_1("date_1", "text_1", 0, 0);
    CommentBL comment_2("date_2", "text_2", 1, 0);
    std::vector<CommentBL> comments = { comment_1, comment_2 };
    CommentRepository comment_repo(comments);

    ClientController client_controller(0, &post_repo, &comment_repo, &user_repo);
    std::vector<PostBL> getting_posts = client_controller.get_posts("date_1", "", "", "");
    EXPECT_EQ(getting_posts.size(), 1);
    EXPECT_EQ(getting_posts[0], post_1);
}


TEST(CONTROLLER_CLIENT_TEST, UPDATE_USER)
{
    std::string name_1 = "name_1";
    std::string surname_1 = "surname_1";
    std::string login_1 = "login_1";
    std::string password_1 = "password_1";
    std::string city_1 = "city_1";
    std::string access_1 = "C";
    std::vector<PostBL> posts_1;

    UserBL user_1(name_1, surname_1, login_1, password_1, city_1, access_1, posts_1);
    UserBL user_2("name_2", "surname_2", "login_2", "password_2", "city_2", "C", {});
    std::vector<UserBL> users = { user_1, user_2 };
    UserRepository user_repo(users);

    PostBL post_1("name_1", 0, "info_1", "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", "organizer_2", "date_2", false);
    std::vector<PostBL> posts = { post_1, post_2 };
    PostRepository post_repo(posts);

    CommentBL comment_1("date_1", "text_1", 0, 0);
    CommentBL comment_2("date_2", "text_2", 1, 0);
    std::vector<CommentBL> comments = { comment_1, comment_2 };
    CommentRepository comment_repo(comments);

    std::string surname_3 = "surname_3";
    int id = 0;
    UserBL user(name_1, surname_3, login_1, password_1, city_1, access_1, {});

    ClientController client_controller(id, &post_repo, &comment_repo, &user_repo);
    UserBL updating_user = client_controller.update("", surname_3, "", "", "");

    EXPECT_EQ(updating_user, user);
    EXPECT_EQ(user_repo.get_user(id), user);
}
