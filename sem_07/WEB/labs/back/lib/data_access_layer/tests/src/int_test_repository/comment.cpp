#include <gtest/gtest.h>

#include "database/pg_database_async.h"
#include "repository/comment.h"

#include "builder/user.h"
#include "builder/post.h"
#include "builder/comment.h"


TEST(REPOSITORY_COMMENT_INT_TEST, GET_COMMENT)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    CommentBL comment = CommentBuilder()
                        .with_author_id(user_id)
                        .with_post_id(post_id)
                        .build(false);
    add_comment_to_db(db, comment);
    int comment_id = db->get_comment_id(Comment(comment));

    auto comment_repo = std::make_shared<CommentRepository>(db);

    // Act
    CommentBL get_comment = comment_repo->get_comment(comment_id);

    // Assert
    EXPECT_EQ(get_comment, comment);

    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_COMMENT_INT_TEST, GET_COMMENT_ID)
{
    // Arrange 
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    CommentBL comment = CommentBuilder()
                        .with_author_id(user_id)
                        .with_post_id(post_id)
                        .build(false);
    add_comment_to_db(db, comment);
    int comment_id = db->get_comment_id(Comment(comment));

    auto comment_repo = std::make_shared<CommentRepository>(db);

    // Act
    int get_comment_id = comment_repo->get_comment_id(comment);

    // Assert
    EXPECT_EQ(get_comment_id, comment_id);

    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_COMMENT_INT_TEST, GET_COMMENTS_BY_POST_ID)
{
    // Arrange 
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    CommentBL comment = CommentBuilder()
                        .with_author_id(user_id)
                        .with_post_id(post_id)
                        .build(false);
    add_comment_to_db(db, comment);

    auto comment_repo = std::make_shared<CommentRepository>(db);

    // Act
    std::vector<CommentBL> get_comments = comment_repo->get_comments(post_id);

    // Assert
    EXPECT_EQ(get_comments.size(), 1);
    EXPECT_EQ(get_comments[0], comment);

    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_COMMENT_INT_TEST, ADD_COMMENT)
{
    // Arrange 
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    CommentBL comment = CommentBuilder()
                        .with_author_id(user_id)
                        .with_post_id(post_id)
                        .build(false);

    auto comment_repo = std::make_shared<CommentRepository>(db);

    // Act
    CommentBL add_comment = comment_repo->add_comment(
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


TEST(REPOSITORY_COMMENT_INT_TEST, DELETE_COMMENT)
{
    // Arrange 
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    CommentBL comment = CommentBuilder()
                        .with_author_id(user_id)
                        .with_post_id(post_id)
                        .build(false);
    add_comment_to_db(db, comment);
    int comment_id = db->get_comment_id(Comment(comment));

    auto comment_repo = std::make_shared<CommentRepository>(db);

    // Act
    CommentBL del_comment = comment_repo->delete_comment(comment_id);

    // Assert
    EXPECT_EQ(del_comment, comment);
    EXPECT_EQ(comment_repo->get_comments(post_id).size(), 0);

    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}


TEST(REPOSITORY_COMMENT_INT_TEST, UPDATE_COMMENT)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    PostBL post = PostBuilder().with_author_id(user_id).build(false);
    add_post_to_db(db, post);
    int post_id = db->get_post_id(Post(post));

    CommentBL comment = CommentBuilder()
                        .with_author_id(user_id)
                        .with_post_id(post_id)
                        .build(false);
    std::string new_text = "new_text";
    add_comment_to_db(db, comment);
    int comment_id = db->get_comment_id(Comment(comment));

    auto comment_repo = std::make_shared<CommentRepository>(db);

    // Act
    CommentBL upd_comment = comment_repo->update_comment(comment_id, "", new_text);

    // Assert
    EXPECT_EQ(comment_repo->get_comment(comment_id).get_text(), new_text);
    
    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}