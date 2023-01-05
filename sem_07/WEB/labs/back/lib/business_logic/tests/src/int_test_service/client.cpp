#include <gtest/gtest.h>

#include "service/client.h"

#include "builder/user.h"
#include "builder/post.h"
#include "builder/comment.h"

#include "database/pg_database_async.h"
#include "repository/user.h"
#include "repository/post.h"
#include "repository/comment.h"


TEST(SERVICE_CLIENT_TEST, ADD_COMMENT)
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


// TEST(SERVICE_CLIENT_TEST, GET_POSTS_BY_FILTERS)
// {
//     // Arrange
//     auto post_builder = PostBuilder();
//     PostBL post_1 = post_builder.with_date("01.01.1970").build(false);
//     PostBL post_2 = post_builder.with_date("02.01.1970").build(false);

//     auto user_repo = new TestUserRepository(std::vector<UserBL>());
//     auto post_repo = new TestPostRepository({ post_1, post_2 }); 
//     auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
//     auto service = ClientService(
//         std::shared_ptr<TestPostRepository>(post_repo),
//         std::shared_ptr<TestCommentRepository>(comment_repo),
//         std::shared_ptr<TestUserRepository>(user_repo)
//     );

//     // Act
//     std::vector<PostBL> get_posts = service.get_posts(post_1.get_date(), "", "", "");

//     // Assert
//     EXPECT_EQ(get_posts[0], post_1);
//     EXPECT_EQ(get_posts.size(), 1);
// }


// TEST(SERVICE_CLIENT_TEST, UPDATE_USER)
// {
//     // Arrange
//     UserBL user = UserBuilder().build();

//     auto user_repo = new TestUserRepository({ user });
//     auto post_repo = new TestPostRepository(std::vector<PostBL>()); 
//     auto comment_repo = new TestCommentRepository(std::vector<CommentBL>());  
//     auto service = ClientService(
//         std::shared_ptr<TestPostRepository>(post_repo),
//         std::shared_ptr<TestCommentRepository>(comment_repo),
//         std::shared_ptr<TestUserRepository>(user_repo)
//     );

//     // Act
//     UserBL upd_user = service.update(0, "new_name", "", "", "", "");

//     // Assert
//     EXPECT_EQ(upd_user, user_repo->get_user(0));
//     EXPECT_EQ(user_repo->get_user(0).get_name(), "new_name");
// }
