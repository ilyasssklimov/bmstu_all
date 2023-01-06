#include <gtest/gtest.h>

#include "service/admin.h"

#include "builder/user.h"
#include "builder/post.h"
#include "builder/comment.h"

#include "database/pg_database_async.h"
#include "repository/user.h"
#include "repository/post.h"
#include "repository/comment.h"


TEST(SERVICE_ADMIN_INT_TEST, GET_WAITING_POSTS)
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

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = AdminService(post_repo, comment_repo, user_repo);

    // Act
    std::vector<PostBL> posts = service.get_waiting_posts();

    // Assert
    EXPECT_EQ(posts.size(), 1);
    EXPECT_EQ(posts[0], post_2);

    db->delete_posts();
    db->delete_users();
}


TEST(SERVICE_ADMIN_INT_TEST, SUBMIT_POST)
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

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = AdminService(post_repo, comment_repo, user_repo);

    // Act
    PostBL sub_post = service.submit_post(db->get_post_id(Post(post_2)));

    // Assert
    EXPECT_EQ(service.get_waiting_posts().size(), 1);
    EXPECT_EQ(post_repo->get_posts().size(), 1);
    EXPECT_EQ(post_repo->get_posts()[0].get_visible(), true);
    EXPECT_EQ(post_repo->get_posts()[0], sub_post);

    db->delete_posts();
    db->delete_users();
}


TEST(SERVICE_ADMIN_INT_TEST, DELETE_USER)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = AdminService(post_repo, comment_repo, user_repo);

    // Act
    UserBL del_user = service.delete_user(user_id);

    // Assert
    EXPECT_EQ(service.get_users().size(), 0);
    EXPECT_EQ(del_user, user);

    db->delete_users();
}


TEST(SERVICE_ADMIN_INT_TEST, DELETE_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder()
                  .with_name("name_1")
                  .with_author_id(user_id)
                  .build(false);

    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));
    do_visible_post(db, post_id, post);

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = AdminService(post_repo, comment_repo, user_repo);

    // Act
    PostBL del_post = service.delete_post(post_id);

    // Assert
    EXPECT_EQ(post_repo->get_posts().size(), 0);
    EXPECT_EQ(del_post, post);

    db->delete_posts();
    db->delete_users();
}


TEST(SERVICE_ADMIN_INT_TEST, DELETE_COMMENT)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder()
                  .with_name("name_1")
                  .with_author_id(user_id)
                  .build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    CommentBL comment = CommentBuilder()
                        .with_author_id(user_id)
                        .with_post_id(post_id)
                        .build(false);
    add_comment_to_db(db, comment);
    int comment_id = db->get_comment_id(Comment(comment));

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = AdminService(post_repo, comment_repo, user_repo);

    // Act
    CommentBL del_comment = service.delete_comment(comment_id);

    // Assert
    EXPECT_EQ(service.get_comments(post_id).size(), 0);
    EXPECT_EQ(del_comment, comment);

    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}