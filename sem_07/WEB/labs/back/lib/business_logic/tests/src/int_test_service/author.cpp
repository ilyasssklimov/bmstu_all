#include <gtest/gtest.h>

#include "service/author.h"

#include "builder/user.h"
#include "builder/post.h"
#include "builder/comment.h"

#include "database/pg_database_async.h"
#include "repository/user.h"
#include "repository/post.h"
#include "repository/comment.h"


TEST(SERVICE_AUTHOR_INT_TEST, CREATE_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder()
                  .with_author_id(user_id)
                  .build(false);

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = AuthorService(post_repo, comment_repo, user_repo);

    // Act
    PostBL add_post = service.create_post(
        post.get_author_id(),
        post.get_name(),
        post.get_information(),
        post.get_city(),
        post.get_organizer(),
        post.get_date()
    );

    // Assert
    EXPECT_EQ(add_post, post);
    EXPECT_EQ(post_repo->get_post(db->get_post_id(Post(post))), post);

    db->delete_posts();
    db->delete_users();
}


TEST(SERVICE_AUTHOR_INT_TEST, DELETE_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder()
                  .with_author_id(user_id)
                  .build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = AuthorService(post_repo, comment_repo, user_repo);

    // Act
    PostBL del_post = service.delete_post(post_id);

    // Assert
    EXPECT_EQ(del_post, post);
    EXPECT_EQ(post_repo->get_posts().size(), 1);

    db->delete_posts();
    db->delete_users();
}


TEST(SERVICE_AUTHOR_INT_TEST, UPDATE_POST)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder()
                  .with_author_id(user_id)
                  .build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = AuthorService(post_repo, comment_repo, user_repo);

    // Act
    PostBL upd_post = service.update_post(post_id, "new_name", "", "", "");

    // Assert
    EXPECT_EQ(upd_post.get_name(), "new_name");
    EXPECT_EQ(upd_post, post_repo->get_post(post_id));

    db->delete_posts();
    db->delete_users();
}