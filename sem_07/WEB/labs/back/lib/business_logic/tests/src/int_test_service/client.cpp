#include <gtest/gtest.h>

#include "service/client.h"

#include "builder/user.h"
#include "builder/post.h"
#include "builder/comment.h"

#include "database/pg_database_async.h"
#include "repository/user.h"
#include "repository/post.h"
#include "repository/comment.h"


TEST(SERVICE_CLIENT_INT_TEST, ADD_COMMENT)
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

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = ClientService(post_repo, comment_repo, user_repo);

    // Act
    CommentBL add_comment = service.add_comment(
        comment.get_date(),
        comment.get_text(),
        comment.get_author_id(),
        comment.get_post_id()
    );

    // Assert
    EXPECT_EQ(add_comment, comment);
    EXPECT_EQ(comment_repo->get_comments(post_id).size(), 1);
    EXPECT_EQ(comment_repo->get_comments(post_id)[0], comment);


    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}


TEST(SERVICE_CLIENT_INT_TEST, GET_POSTS_BY_FILTERS)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    auto builder = PostBuilder();
    PostBL post_1 = builder
                    .with_date("01.01.1970")
                    .with_author_id(user_id)
                    .build(false);
    PostBL post_2 = builder
                    .with_date("02.01.1970")
                    .with_author_id(user_id)
                    .build(false);

    add_post_to_db(db, post_1);
    add_post_to_db(db, post_2);

    int id_1 = db->get_post_id(Post(post_1));
    int id_2 = db->get_post_id(Post(post_2));
    
    do_visible_post(db, id_1, post_1);
    do_visible_post(db, id_2, post_2);

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = ClientService(post_repo, comment_repo, user_repo);

    // Act
    std::vector<PostBL> posts = service.get_posts(post_1.get_date(), "", "", "");

    // Assert
    EXPECT_EQ(posts[0], post_1);
    EXPECT_EQ(posts.size(), 1);

    db->delete_posts();
    db->delete_users();
}


TEST(SERVICE_CLIENT_INT_TEST, UPDATE_USER)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);
    auto comment_repo = std::make_shared<CommentRepository>(db);
    auto service = ClientService(post_repo, comment_repo, user_repo);

    // Act
    UserBL upd_user = service.update(user_id, "new_name", "", "", "", "");

    // Assert
    EXPECT_EQ(upd_user, user_repo->get_user(user_id));
    EXPECT_EQ(user_repo->get_user(user_id).get_name(), "new_name");

    db->delete_users();
}
