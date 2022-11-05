#include <gtest/gtest.h>
#include "test_post_repository.h"
#include "test_post_repository.h"


TEST(CONTROLLER_GUEST_TEST, GET_POST)
{
    PostBL post_1("name_1", 0, "info_1", "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", "organizer_2", "date_2", false);
    std::vector<PostBL> posts = { post_1, post_2 };
    PostRepository post_repo(posts);
    UserRepository user_repo({});

    GuestController guest_controller(&post_repo, &user_repo);
    PostBL getting_post_1 = guest_controller.get_post(0);
    PostBL getting_post_2 = guest_controller.get_post(1);

    EXPECT_EQ(getting_post_1, post_1);
    EXPECT_EQ(getting_post_2, post_2);
}


TEST(CONTROLLER_GUEST_TEST, GET_POSTS_BY_IDS)
{
    PostBL post_1("name_1", 0, "info_1", "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", "organizer_2", "date_2", false);
    PostBL post_3("name_2", 2, "info_3", "city_3", "organizer_3", "date_3", false);
    std::vector<PostBL> posts = { post_1, post_2, post_3 };
    PostRepository post_repo(posts);
    UserRepository user_repo({});

    GuestController guest_controller(&post_repo, &user_repo);
    std::vector<int> post_ids = { 0, 2 };
    std::vector<PostBL> getting_posts = guest_controller.get_posts(post_ids);

    EXPECT_EQ(getting_posts.size(), 2);
    EXPECT_EQ(getting_posts[0], post_1);
    EXPECT_EQ(getting_posts[1], post_3);
}


TEST(CONTROLLER_GUEST_TEST, GET_ALL_POSTS)
{
    PostBL post_1("name_1", 0, "info_1", "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", "organizer_2", "date_2", false);
    PostBL post_3("name_2", 2, "info_3", "city_3", "organizer_3", "date_3", false);
    std::vector<PostBL> posts = { post_1, post_2, post_3 };
    PostRepository post_repo(posts);
    UserRepository user_repo({});

    GuestController guest_controller(&post_repo, &user_repo);
    std::vector<PostBL> getting_posts = guest_controller.get_posts();

    EXPECT_EQ(getting_posts.size(), 3);
    EXPECT_EQ(getting_posts[0], post_1);
    EXPECT_EQ(getting_posts[1], post_2);
    EXPECT_EQ(getting_posts[2], post_3);
}


TEST(CONTROLLER_GUEST_TEST, GET_POST_INFO)
{
    std::string info_1 = "info_1";
    std::string info_2 = "info_2";
    PostBL post_1("name_1", 0, info_1, "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, info_2, "city_2", "organizer_2", "date_2", false);
    std::vector<PostBL> posts = { post_1, post_2 };
    PostRepository post_repo(posts);
    UserRepository user_repo({});

    GuestController guest_controller(&post_repo, &user_repo);
    std::string getting_info_1 = guest_controller.get_post_info(0);
    std::string getting_info_2 = guest_controller.get_post_info(1);

    EXPECT_EQ(getting_info_1, info_1);
    EXPECT_EQ(getting_info_2, info_2);
}


TEST(CONTROLLER_GUEST_TEST, SIGN_IN)
{
    PostBL post_1("name_1", 0, "info_1", "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", "organizer_2", "date_2", false);
    std::vector<PostBL> posts = { post_1, post_2 };
    PostRepository post_repo(posts);
    UserRepository user_repo({});

    std::string name_1 = "name_1";
    std::string surname_1 = "surname_1";
    std::string login_1 = "login_1";
    std::string password_1 = "password_1";
    std::string city_1 = "city_1";
    std::string access_1 = "client";
    UserBL user(name_1, surname_1, login_1, password_1, city_1, access_1);

    GuestController guest_controller(&post_repo, &user_repo);
    UserBL adding_user = guest_controller.sign_in(name_1, surname_1, login_1, password_1, city_1, access_1);

    EXPECT_EQ(adding_user, user);
    EXPECT_EQ(user_repo.get_users().size(), 1);
    EXPECT_EQ(user_repo.get_users()[0], user);
}


TEST(CONTROLLER_GUEST_TEST, LOG_IN)
{
    PostBL post_1("name_1", 0, "info_1", "city_1", "organizer_1", "date_1", false);
    PostBL post_2("name_2", 1, "info_2", "city_2", "organizer_2", "date_2", false);
    std::vector<PostBL> posts = { post_1, post_2 };
    PostRepository post_repo(posts);

    UserBL user_1("name_1", "surname_1", "login_1", "password_1", "city_1", "C", {});
    UserBL user_2("name_2", "surname_2", "login_2", "password_2", "city_2", "C", {});
    std::vector<UserBL> users = { user_1, user_2 };
    UserRepository user_repo(users);

    GuestController guest_controller(&post_repo, &user_repo);
    UserBL log_in_result = guest_controller.log_in("login_2", "password_2");

    EXPECT_TRUE((bool) log_in_result);
}


