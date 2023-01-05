#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock_database/database.h"
#include "repository/comment.h"
#include "builder/comment.h"


TEST(REPOSITORY_COMMENT_TEST, GET_COMMENT)
{
    // Arrange 
    auto mock_db = new MockDatabase();
    CommentBL comment = CommentBuilder().build();
    int comment_id = 0;

    EXPECT_CALL(*mock_db, get_comment(comment_id)).WillOnce(testing::Return(Comment(comment)));
    
    auto comment_repo = CommentRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    CommentBL get_comment = comment_repo.get_comment(comment_id);

    // Assert
    EXPECT_EQ(get_comment, comment);
}


TEST(REPOSITORY_COMMENT_TEST, GET_COMMENT_ID)
{
    // Arrange 
    auto mock_db = new MockDatabase();
    CommentBL comment = CommentBuilder().build();
    int comment_id = 0;

    EXPECT_CALL(*mock_db, get_comment_id(Comment(comment))).WillOnce(testing::Return(comment_id));
    
    auto comment_repo = CommentRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    int get_comment_id = comment_repo.get_comment_id(comment);

    // Assert
    EXPECT_EQ(get_comment_id, comment_id);
}


TEST(REPOSITORY_COMMENT_TEST, GET_COMMENTS_BY_POST_UD)
{
    // Arrange 
    auto mock_db = new MockDatabase();
    auto builder = CommentBuilder();
    CommentBL comment_1 = builder.build();
    CommentBL comment_2 = builder.build();
    std::vector<CommentBL> comments_bl = { comment_1, comment_2 };
    std::vector<Comment> comments = { Comment(comment_1), Comment(comment_2) };
    int post_id = 0;

    EXPECT_CALL(*mock_db, get_comments(post_id)).WillOnce(testing::Return(comments));
    
    auto comment_repo = CommentRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    std::vector<CommentBL> get_comments = comment_repo.get_comments(post_id);

    // Assert
    EXPECT_EQ(get_comments, comments_bl);
}


TEST(REPOSITORY_COMMENT_TEST, ADD_COMMENT)
{
    // Arrange 
    auto mock_db = new MockDatabase();
    CommentBL comment = CommentBuilder().build();

    EXPECT_CALL(*mock_db, add_comment(
        comment.get_date(),
        comment.get_text(),
        comment.get_author_id(),
        comment.get_post_id()
    )).WillOnce(testing::Return(Comment(comment)));
    
    auto comment_repo = CommentRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    CommentBL add_comment = comment_repo.add_comment(
        comment.get_date(),
        comment.get_text(),
        comment.get_author_id(),
        comment.get_post_id()
    );

    // Assert
    EXPECT_EQ(add_comment, comment);
}


TEST(REPOSITORY_COMMENT_TEST, DELETE_COMMENT)
{
    // Arrange 
    auto mock_db = new MockDatabase();
    CommentBL comment = CommentBuilder().build();
    int comment_id = 0;

    EXPECT_CALL(*mock_db, delete_comment(comment_id)).WillOnce(testing::Return(Comment(comment)));
    
    auto comment_repo = CommentRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    CommentBL del_comment = comment_repo.delete_comment(comment_id);

    // Assert
    EXPECT_EQ(del_comment, comment);
}


TEST(REPOSITORY_COMMENT_TEST, UPDATE_COMMENT)
{
    // Arrange
    auto mock_db = new MockDatabase();
    std::string new_text = "new_text";

    auto builder = CommentBuilder();
    CommentBL comment = builder.build();
    CommentBL new_comment = builder.with_text(new_text).build(false);
    int comment_id = 0;

    EXPECT_CALL(*mock_db, update_comment(
        comment_id,
        comment.get_date(),
        new_text
    )).WillOnce(testing::Return(new_comment));
    
    EXPECT_CALL(*mock_db, get_comment(comment_id)).WillOnce(testing::Return(comment));
    
    auto comment_repo = CommentRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    CommentBL upd_comment = comment_repo.update_comment(comment_id, "", new_text);

    // Assert
    EXPECT_EQ(upd_comment, new_comment);
}