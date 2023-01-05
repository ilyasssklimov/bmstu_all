#include <gtest/gtest.h>

#include "service/author.h"

#include "builder/user.h"
#include "builder/post.h"
#include "builder/comment.h"

#include "test_repository/user.h"
#include "test_repository/post.h"
#include "test_repository/comment.h"


TEST(SERVICE_AUTHOR_TEST, CREATE_POST)
{
    // Arrange
    PostBL post = PostBuilder().build();

    auto user_repo = new TestUserRepository(std::vector<UserBL>());
    auto post_repo = new TestPostRepository(std::vector<PostBL>()); 
    auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
    auto service = AuthorService(
        std::shared_ptr<TestPostRepository>(post_repo),
        std::shared_ptr<TestCommentRepository>(comment_repo),
        std::shared_ptr<TestUserRepository>(user_repo)
    );

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
    EXPECT_EQ(add_post, post_repo->get_post(0));
}


TEST(SERVICE_AUTHOR_TEST, DELETE_POST)
{
    // Arrange
    PostBL post = PostBuilder().build();

    auto user_repo = new TestUserRepository(std::vector<UserBL>());
    auto post_repo = new TestPostRepository({ post }); 
    auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
    auto service = AuthorService(
        std::shared_ptr<TestPostRepository>(post_repo),
        std::shared_ptr<TestCommentRepository>(comment_repo),
        std::shared_ptr<TestUserRepository>(user_repo)
    );

    // Act
    PostBL del_post = service.delete_post(0);

    // Assert
    EXPECT_EQ(del_post, post);
    EXPECT_EQ(post_repo->get_posts().size(), 0);
}


TEST(SERVICE_AUTHOR_TEST, UPDATE_POST)
{
    // Arrange
    PostBL post = PostBuilder().build();

    auto user_repo = new TestUserRepository(std::vector<UserBL>());
    auto post_repo = new TestPostRepository({ post }); 
    auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
    auto service = AuthorService(
        std::shared_ptr<TestPostRepository>(post_repo),
        std::shared_ptr<TestCommentRepository>(comment_repo),
        std::shared_ptr<TestUserRepository>(user_repo)
    );

    // Act
    PostBL upd_post = service.update_post(0, "new_name", "", "", "");

    // Assert
    EXPECT_EQ(upd_post.get_name(), "new_name");
    EXPECT_EQ(upd_post, post_repo->get_post(0));

}