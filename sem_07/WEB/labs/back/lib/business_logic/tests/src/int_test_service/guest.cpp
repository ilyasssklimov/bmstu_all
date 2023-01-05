#include <gtest/gtest.h>

#include "service/guest.h"

#include "database/pg_database_async.h"
#include "repository/user.h"
#include "repository/post.h"

#include "builder/user.h"
#include "builder/post.h"


std::unordered_map<size_t, std::shared_ptr<void>> ServiceLocator::_instances;

TEST(INTEGRATION_TESTS, GUEST_SERVICE)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    auto user_repo = std::make_shared<UserRepository>(db);
    auto post_repo = std::make_shared<PostRepository>(db);

    auto service = GuestService(post_repo, user_repo);

    // Act
    UserBL add_user = service.sign_up(
        user.get_name(),
        user.get_surname(),
        user.get_login(),
        user.get_password(),
        user.get_city(),
        user.get_access()
    );

    // Assert
    EXPECT_EQ(add_user, user);
    EXPECT_EQ(user_repo->get_users().size(), 1);
    EXPECT_EQ(user_repo->get_users()[0], user);
}


// TEST(SERVICE_GUEST_TEST, SIGN_IN)
// {
//     // Arrange
//     UserBL user = UserBuilder().build();

//     auto user_repo = new UserRepository({ user });
//     auto post_repo = new PostRepository(std::vector<PostBL>());   
//     auto service = GuestService(
//         std::shared_ptr<PostRepository>(post_repo),
//         std::shared_ptr<UserRepository>(user_repo)
//     );

//     // Act
//     UserBL yes_user = service.sign_in(user.get_login(), user.get_password());
//     UserBL no_user = service.sign_in("login_false", "password_false");

//     // Assert
//     EXPECT_TRUE((bool) yes_user);
//     EXPECT_FALSE((bool) no_user);
// }


// TEST(SERVICE_GUEST_TEST, GET_USERS)
// {
//     // Arrange
//     auto builder = UserBuilder();
//     UserBL user_1 = builder.build();
//     UserBL user_2 = builder.build();

//     auto user_repo = new UserRepository({ user_1, user_2 });
//     auto post_repo = new PostRepository(std::vector<PostBL>());   
//     auto service = GuestService(
//         std::shared_ptr<PostRepository>(post_repo),
//         std::shared_ptr<UserRepository>(user_repo)
//     );

//     // Act
//     std::vector<UserBL> users = service.get_users();

//     // Assert
//     EXPECT_EQ(users[0], user_1);
//     EXPECT_EQ(users[1], user_2);
//     EXPECT_EQ(users.size(), 2);
// }


// TEST(SERVICE_GUEST_TEST, GET_USER)
// {
//     // Arrange
//     auto builder = UserBuilder();
//     UserBL user_1 = builder.build();
//     UserBL user_2 = builder.build();

//     auto user_repo = new UserRepository({ user_1, user_2 });
//     auto post_repo = new PostRepository(std::vector<PostBL>());   
//     auto service = GuestService(
//         std::shared_ptr<PostRepository>(post_repo),
//         std::shared_ptr<UserRepository>(user_repo)
//     );

//     // Act
//     UserBL get_user_1 = service.get_user(0);
//     UserBL get_user_2 = service.get_user(1);

//     // Assert
//     EXPECT_EQ(get_user_1, user_1);
//     EXPECT_EQ(get_user_2, user_2);
// }


// TEST(SERVICE_GUEST_TEST, GET_POSTS)
// {
//     // Arrange
//     auto builder = PostBuilder();
//     PostBL post_1 = builder.build();
//     PostBL post_2 = builder.build();

//     auto user_repo = new UserRepository(std::vector<UserBL>());
//     auto post_repo = new PostRepository({ post_1, post_2 });   
//     auto service = GuestService(
//         std::shared_ptr<PostRepository>(post_repo),
//         std::shared_ptr<UserRepository>(user_repo)
//     );

//     // Act
//     std::vector<PostBL> posts = service.get_posts();

//     // Assert
//     EXPECT_EQ(posts[0], post_1);
//     EXPECT_EQ(posts[1], post_2);
//     EXPECT_EQ(posts.size(), 2);
// }


// TEST(SERVICE_GUEST_TEST, GET_POST)
// {
//     // Arrange
//     auto builder = PostBuilder();
//     PostBL post_1 = builder.build();
//     PostBL post_2 = builder.build();

//     auto user_repo = new UserRepository(std::vector<UserBL>());
//     auto post_repo = new PostRepository({ post_1, post_2 });   
//     auto service = GuestService(
//         std::shared_ptr<PostRepository>(post_repo),
//         std::shared_ptr<UserRepository>(user_repo)
//     );

//     // Act
//     PostBL get_post_1 = service.get_post(0);
//     PostBL get_post_2 = service.get_post(1);

//     // Assert
//     EXPECT_EQ(get_post_1, post_1);
//     EXPECT_EQ(get_post_2, post_2);
// }
