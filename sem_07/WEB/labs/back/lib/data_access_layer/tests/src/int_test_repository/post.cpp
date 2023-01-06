#include <gtest/gtest.h>

#include "database/pg_database_async.h"
#include "repository/post.h"

#include "builder/user.h"
#include "builder/post.h"


TEST(REPOSITORY_POST_INT_TEST, GET_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    PostBL get_post = post_repo->get_post(post_id);

    // Assert
    EXPECT_EQ(get_post, post);

    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_POST_INT_TEST, GET_POST_ID)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    int get_post_id = post_repo->get_post_id(post);

    // Assert
    EXPECT_EQ(get_post_id, post_id);

    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_POST_INT_TEST, GET_POSTS)
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
    do_visible_post(db, db->get_post_id(Post(post_1)), post_1);
    do_visible_post(db, db->get_post_id(Post(post_2)), post_2);

    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    std::vector<PostBL> get_posts = post_repo->get_posts();

    // Assert
    EXPECT_EQ(get_posts.size(), 2);
    EXPECT_EQ(get_posts[0], post_1);
    EXPECT_EQ(get_posts[1], post_2);

    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_POST_INT_TEST, GET_POSTS_BY_FILTERS)
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
    do_visible_post(db, db->get_post_id(Post(post_1)), post_1);
    do_visible_post(db, db->get_post_id(Post(post_2)), post_2);

    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    std::vector<PostBL> get_posts = post_repo->get_posts("", post_2.get_name(), "", "");

    // Assert
    EXPECT_EQ(get_posts.size(), 1);
    EXPECT_EQ(get_posts[0], post_2);

    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_POST_INT_TEST, GET_UNVISIBLE_POSTS)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);

    int post_id = db->get_post_id(Post(post));
    db->update_post(
        post_id, 
        post.get_name(),
        post.get_information(),
        post.get_city(),
        post.get_date(),
        false
    );

    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    std::vector<PostBL> get_posts = post_repo->get_unvisible_posts();

    // Assert
    EXPECT_EQ(get_posts.size(), 1);
    EXPECT_EQ(get_posts[0], post);

    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_POST_INT_TEST, ADD_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    PostBL add_post = post_repo->add_post(
        post.get_name(),
        post.get_author_id(),
        post.get_information(),
        post.get_city(),
        post.get_organizer(),
        post.get_date()
    );

    // Assert
    EXPECT_EQ(add_post, post);
    EXPECT_EQ(post_repo->get_unvisible_posts().size(), 1);
    EXPECT_EQ(post_repo->get_unvisible_posts()[0], post);

    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_POST_INT_TEST, DELETE_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    PostBL del_post = post_repo->delete_post(post_id);

    // Assert
    EXPECT_EQ(del_post, post);
    EXPECT_EQ(post_repo->get_unvisible_posts().size(), 0);

    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_POST_INT_TEST, UPDATE_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();
    std::string new_name = "new_name";

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    PostBL upd_post = post_repo->update_post(post_id, new_name, "", "", "");

    // Assert
    EXPECT_EQ(post_repo->get_post(post_id).get_name(), new_name);

    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_POST_INT_TEST, UPDATE_POST_VISIBLE)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    auto post_repo = std::make_shared<PostRepository>(db);

    // Act
    PostBL upd_post = post_repo->update_post(post_id, true);

    // Assert
    EXPECT_EQ(post_repo->get_posts().size(), 1);
    EXPECT_EQ(post_repo->get_unvisible_posts().size(), 0);
    EXPECT_EQ(post_repo->get_post(post_id).get_visible(), true);

    db->delete_posts();
    db->delete_users();
}