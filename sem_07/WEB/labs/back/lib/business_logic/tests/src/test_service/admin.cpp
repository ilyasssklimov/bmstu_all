#include <gtest/gtest.h>

#include "service/admin.h"

#include "builder/user.h"
#include "builder/post.h"
#include "builder/comment.h"

#include "test_repository/user.h"
#include "test_repository/post.h"
#include "test_repository/comment.h"


TEST(SERVICE_ADMIN_TEST, GET_WAITING_POSTS)
{
    // Arrange
    auto builder = PostBuilder();
    PostBL post_1 = builder
                    .with_name("name_1")
                    .with_visible(false)
                    .build(false);
    PostBL post_2 = builder
                    .with_visible(true)
                    .with_name("name_2")
                    .build(false);

    auto user_repo = new TestUserRepository(std::vector<UserBL>());
    auto post_repo = new TestPostRepository({ post_1, post_2 }); 
    auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
    auto service = AdminService(
        std::shared_ptr<TestPostRepository>(post_repo),
        std::shared_ptr<TestCommentRepository>(comment_repo),
        std::shared_ptr<TestUserRepository>(user_repo)
    );

    // Act
    std::vector<PostBL> posts = service.get_waiting_posts();

    // Assert
    EXPECT_EQ(posts.size(), 1);
    EXPECT_EQ(posts[0], post_1);
}


TEST(SERVICE_ADMIN_TEST, SUBMIT_POST)
{
    // Arrange
    auto builder = PostBuilder();
    PostBL post= builder
                 .with_name("name_1")
                 .with_visible(false)
                 .build(false);

    auto user_repo = new TestUserRepository(std::vector<UserBL>());
    auto post_repo = new TestPostRepository({ post }); 
    auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
    auto service = AdminService(
        std::shared_ptr<TestPostRepository>(post_repo),
        std::shared_ptr<TestCommentRepository>(comment_repo),
        std::shared_ptr<TestUserRepository>(user_repo)
    );

    // Act
    PostBL sub_post = service.submit_post(0);

    // Assert
    EXPECT_EQ(service.get_waiting_posts().size(), 0);
    EXPECT_EQ(post_repo->get_posts()[0].get_visible(), true);
    EXPECT_EQ(post_repo->get_posts()[0], sub_post);
}


TEST(SERVICE_ADMIN_TEST, DELETE_USER)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto user_repo = new TestUserRepository({ user });
    auto post_repo = new TestPostRepository(std::vector<PostBL>()); 
    auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
    auto service = AdminService(
        std::shared_ptr<TestPostRepository>(post_repo),
        std::shared_ptr<TestCommentRepository>(comment_repo),
        std::shared_ptr<TestUserRepository>(user_repo)
    );

    // Act
    UserBL del_user = service.delete_user(0);

    // Assert
    EXPECT_EQ(service.get_users().size(), 0);
    EXPECT_EQ(del_user, user);
}


TEST(SERVICE_ADMIN_TEST, DELETE_POST)
{
    // Arrange
    PostBL post = PostBuilder().build();

    auto user_repo = new TestUserRepository(std::vector<UserBL>());
    auto post_repo = new TestPostRepository({ post }); 
    auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
    auto service = AdminService(
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


TEST(SERVICE_ADMIN_TEST, DELETE_COMMENT)
{
    // Arrange
    CommentBL comment = CommentBuilder().build();

    auto user_repo = new TestUserRepository(std::vector<UserBL>());
    auto post_repo = new TestPostRepository(std::vector<PostBL>()); 
    auto comment_repo = new TestCommentRepository({ comment });  
    auto service = AdminService(
        std::shared_ptr<TestPostRepository>(post_repo),
        std::shared_ptr<TestCommentRepository>(comment_repo),
        std::shared_ptr<TestUserRepository>(user_repo)
    );

    // Act
    CommentBL del_comment = service.delete_comment(0);

    // Assert
    EXPECT_EQ(service.get_comments(comment.get_author_id()).size(), 0);
    EXPECT_EQ(del_comment, comment);
}