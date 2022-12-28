#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock_database/database.h"
#include "repository/post.h"
#include "builder/post.h"


TEST(REPOSITORY_POST_TEST, GET_POST)
{
    // Arrange
    auto mock_db = new MockDatabase();
    PostBL post = PostBuilder().build();
    int post_id = 0;

    EXPECT_CALL(*mock_db, get_post(post_id)).WillOnce(testing::Return(Post(post)));
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    PostBL get_post = post_repo.get_post(post_id);

    // Assert
    EXPECT_EQ(get_post, post);
}


TEST(REPOSITORY_POST_TEST, GET_POST_ID)
{
    // Arrange
    auto mock_db = new MockDatabase();
    PostBL post_bl = PostBuilder().build();
    Post post = Post(post_bl);
    int post_id = 0;

    EXPECT_CALL(*mock_db, get_post_id(post)).WillOnce(testing::Return(post_id));
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    int get_post_id = post_repo.get_post_id(post_bl);

    // Assert
    EXPECT_EQ(get_post_id, post_id);
}


TEST(REPOSITORY_POST_TEST, GET_POSTS)
{
    // Arrange
    auto mock_db = new MockDatabase();
    auto builder = PostBuilder();
    PostBL post_1 = builder.build();
    PostBL post_2 = builder.build();
    std::vector<PostBL> posts_bl = { post_1, post_2 };
    std::vector<Post> posts = { Post(post_1), Post(post_2) };

    EXPECT_CALL(*mock_db, get_posts()).WillOnce(testing::Return(posts));
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    std::vector<PostBL> get_posts = post_repo.get_posts();

    // Assert
    EXPECT_EQ(get_posts, posts_bl);
}


TEST(REPOSITORY_POST_TEST, GET_POSTS_BY_FILTERS)
{
    // Arrange
    auto mock_db = new MockDatabase();
    auto builder = PostBuilder();
    PostBL post_1 = builder.with_name("name_1").build(false);
    PostBL post_2 = builder.with_name("name_2").build(false);
    std::vector<PostBL> posts_bl = { post_1, post_2 };
    std::vector<Post> posts = { Post(post_1), Post(post_2) };

    EXPECT_CALL(*mock_db, get_posts(post_2.get_name(), "", "", 0)).WillOnce(
        testing::Return(std::vector<Post>({ Post(post_2) }))
    );
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    std::vector<PostBL> get_posts = post_repo.get_posts(post_2.get_name(), "", "", "");

    // Assert
    EXPECT_EQ(get_posts, std::vector<PostBL>({ post_2 }));
}


TEST(REPOSITORY_POST_TEST, GET_UNVISIBLE_POSTS)
{
    // Arrange
    auto mock_db = new MockDatabase();
    auto builder = PostBuilder();
    PostBL post = builder
                  .with_name("name_1")
                  .with_visible(false)
                  .build(false);
    std::vector<PostBL> posts_bl = { post };
    std::vector<Post> posts = { Post(post) };

    EXPECT_CALL(*mock_db, get_unvisible_posts()).WillOnce(testing::Return(posts));
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    std::vector<PostBL> get_posts = post_repo.get_unvisible_posts();

    // Assert
    EXPECT_EQ(get_posts, posts_bl);
}


TEST(REPOSITORY_POST_TEST, ADD_POST)
{
    // Arrange
    auto mock_db = new MockDatabase();
    PostBL post = PostBuilder().build();

    EXPECT_CALL(*mock_db, add_post(
        post.get_name(),
        post.get_author_id(),
        post.get_information(),
        post.get_city(),
        post.get_organizer(),
        post.get_date()
    )).WillOnce(testing::Return(Post(post)));
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    PostBL add_post = post_repo.add_post(
        post.get_name(),
        post.get_author_id(),
        post.get_information(),
        post.get_city(),
        post.get_organizer(),
        post.get_date()
    );

    // Assert
    EXPECT_EQ(add_post, post);
}


TEST(REPOSITORY_POST_TEST, DELETE_POST)
{
    // Arrange
    auto mock_db = new MockDatabase();
    PostBL post = PostBuilder().build();
    int post_id = 0;

    EXPECT_CALL(*mock_db, delete_post(post_id)).WillOnce(testing::Return(Post(post)));
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    PostBL del_post = post_repo.delete_post(post_id);

    // Assert
    EXPECT_EQ(del_post, post);
}


TEST(REPOSITORY_POST_TEST, UPDATE_POST)
{
    // Arrange
    auto mock_db = new MockDatabase();
    std::string new_name = "new_name";

    auto builder = PostBuilder();
    PostBL post = builder.build();
    PostBL new_post = builder.with_name(new_name).build(false);
    int post_id = 0;

    EXPECT_CALL(*mock_db, update_post(
        post_id,
        new_name,
        post.get_information(),
        post.get_city(),
        post.get_date(),
        post.get_visible()
    )).WillOnce(testing::Return(new_post));
    
    EXPECT_CALL(*mock_db, get_post(post_id)).WillOnce(testing::Return(post));
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    PostBL upd_post = post_repo.update_post(post_id, new_name, "", "", "");

    // Assert
    EXPECT_EQ(upd_post, new_post);
}


TEST(REPOSITORY_POST_TEST, UPDATE_POST_VISIBLE)
{
    // Arrange
    auto mock_db = new MockDatabase();
    auto builder = PostBuilder();

    int post_id = 0;
    PostBL post = builder
                  .with_name("name_1")
                  .with_visible(false)
                  .build(false);
    PostBL new_post = builder.with_visible(true).build(false);
    
    EXPECT_CALL(*mock_db, update_post(
        post_id,
        post.get_name(),
        post.get_information(),
        post.get_city(),
        post.get_date(),
        true
    )).WillOnce(testing::Return(Post(new_post)));
    
    EXPECT_CALL(*mock_db, get_post(post_id)).WillOnce(testing::Return(Post(post)));
    
    auto post_repo = PostRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    PostBL upd_post = post_repo.update_post(post_id, true);

    // Assert
    EXPECT_EQ(upd_post, new_post);
}