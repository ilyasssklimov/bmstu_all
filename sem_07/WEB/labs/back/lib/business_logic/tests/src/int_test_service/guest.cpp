#include <gtest/gtest.h>

#include "service/guest.h"

#include "database/pg_database_async.h"
#include "repository/user.h"
#include "repository/post.h"

#include "builder/user.h"
#include "builder/post.h"


std::unordered_map<size_t, std::shared_ptr<void>> ServiceLocator::_instances;



TEST(SERVICE_GUEST_INT_TEST, SIGN_UP)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);

    auto service = GuestService(post_repo, user_repo);

    // Act
    UserBL add_user = service.sign_up(
        user.get_name(),
        user.get_surname(),
        user.get_login(),
        user.get_password(),
        user.get_city(),
        user.get_access()
    );

    // Assert
    EXPECT_EQ(add_user, user);
    EXPECT_EQ(user_repo->get_users().size(), 1);
    EXPECT_EQ(user_repo->get_users()[0], user);

    db->delete_users();
}


TEST(SERVICE_GUEST_INT_TEST, SIGN_IN)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto service = GuestService(post_repo, user_repo);

    // Act
    UserBL yes_user = service.sign_in(user.get_login(), user.get_password());
    UserBL no_user = service.sign_in("login_fake", "password_fake");

    // Assert
    EXPECT_TRUE((bool) yes_user);
    EXPECT_FALSE((bool) no_user);

    db->delete_users();
}


TEST(SERVICE_GUEST_INT_TEST, GET_USERS)
{
    // Arrange
    auto builder = UserBuilder();
    UserBL user_1 = builder.with_login("login_1").build(false);
    UserBL user_2 = builder.with_login("login_2").build(false);

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user_1);
    add_user_to_db(db, user_2);

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto service = GuestService(post_repo, user_repo);

    // Act
    std::vector<UserBL> users = service.get_users();

    // Assert
    EXPECT_EQ(users[0], user_1);
    EXPECT_EQ(users[1], user_2);
    EXPECT_EQ(users.size(), 2);

    db->delete_users();
}


TEST(SERVICE_GUEST_INT_TEST, GET_USER)
{
    // Arrange
    auto builder = UserBuilder();
    UserBL user_1 = builder.with_login("login_1").build(false);
    UserBL user_2 = builder.with_login("login_2").build(false);

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user_1);
    add_user_to_db(db, user_2);
    int id_1 = db->get_user_id(user_1.get_login());
    int id_2 = db->get_user_id(user_2.get_login());

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto service = GuestService(post_repo, user_repo);

    // Act
    UserBL get_user_1 = service.get_user(id_1);
    UserBL get_user_2 = service.get_user(id_2);

    // Assert
    EXPECT_EQ(get_user_1, user_1);
    EXPECT_EQ(get_user_2, user_2);

    db->delete_users();
}


TEST(SERVICE_GUEST_INT_TEST, GET_POSTS)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    auto builder = PostBuilder();
    PostBL post_1 = builder
                    .with_name("name_1")
                    .with_author_id(user_id)
                    .build(false);
    PostBL post_2 = builder
                    .with_name("name_2")
                    .with_author_id(user_id)
                    .build(false);

    add_post_to_db(db, post_1);
    add_post_to_db(db, post_2);

    int id_1 = db->get_post_id(Post(post_1));
    int id_2 = db->get_post_id(Post(post_2));

    db->update_post(
        id_1,
        post_1.get_name(),
        post_1.get_information(),
        post_1.get_city(),
        post_1.get_date(),
        true
    );
    db->update_post(
        id_2,
        post_2.get_name(),
        post_2.get_information(),
        post_2.get_city(),
        post_2.get_date(),
        true
    );

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto service = GuestService(post_repo, user_repo);

    // Act
    std::vector<PostBL> posts = service.get_posts();

    // Assert
    EXPECT_EQ(posts[0], post_1);
    EXPECT_EQ(posts[1], post_2);
    EXPECT_EQ(posts.size(), 2);

    db->delete_posts();
    db->delete_users();
}


TEST(SERVICE_GUEST_INT_TEST, GET_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    auto builder = PostBuilder();
    PostBL post_1 = builder
                    .with_name("name_1")
                    .with_author_id(user_id)
                    .build(false);
    PostBL post_2 = builder
                    .with_name("name_2")
                    .with_author_id(user_id)
                    .build(false);

    add_post_to_db(db, post_1);
    add_post_to_db(db, post_2);
    int id_1 = db->get_post_id(Post(post_1));
    int id_2 = db->get_post_id(Post(post_2));

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto service = GuestService(post_repo, user_repo);

    // Act
    PostBL get_post_1 = service.get_post(id_1);
    PostBL get_post_2 = service.get_post(id_2);

    // Assert
    EXPECT_EQ(get_post_1, post_1);
    EXPECT_EQ(get_post_2, post_2);

    db->delete_posts();
    db->delete_users();
}
