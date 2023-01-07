#include <gtest/gtest.h>

#include "service/guest.h"
#include "service/author.h"

#include "controller/guest.hpp"
#include "controller/author.hpp"

#include "database/pg_database_async.h"
#include "repository/user.h"
#include "repository/post.h"
#include "repository/comment.h"

#include "locator.hpp"


std::unordered_map<size_t, std::shared_ptr<void>> ServiceLocator::_instances;

TEST(AUTHOR_ACTIONS_E2E_TEST, INTERACTION_POSTS)
{   
    // Arrange 
    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    ServiceLocator::instantiate<PGDatabaseAsync, IDataBase>(db);

    ServiceLocator::instantiate<UserRepository, IUserRepository>();
    ServiceLocator::instantiate<PostRepository, IPostRepository>();
    ServiceLocator::instantiate<CommentRepository, ICommentRepository>();

    ServiceLocator::instantiate<GuestService>();
    ServiceLocator::instantiate<GuestController>();

    ServiceLocator::instantiate<ClientService>();
    ServiceLocator::instantiate<ClientController>();

    ServiceLocator::instantiate<AuthorService>();
    ServiceLocator::instantiate<AuthorController>();

    auto guest_controller = ServiceLocator::resolve<GuestController>();
    auto author_controller = ServiceLocator::resolve<AuthorController>();

    // Get users and posts
    // Act
    auto get_empty_users = guest_controller->get_users();
    auto get_empty_posts = guest_controller->get_posts();

    // Assert
    EXPECT_EQ(get_empty_users.size(), 0);
    EXPECT_EQ(get_empty_posts.size(), 0);

    // Register
    // Act
    auto new_user = guest_controller->sign_up(
        "Ilya",
        "Klimov",
        "ilyasssklimov",
        "password",
        "Yakutsk",
        "A" 
    );

    // Assert
    EXPECT_TRUE((bool) new_user);

    // Instead of authorization
    // int user_id = db->get_user_id("ilyasssklimov");

    // // Get posts
    // // Arrange
    
    // // Act
    // // Assert
    // EXPECT_EQ(add_post, post);
    // EXPECT_EQ(post_repo->get_post(db->get_post_id(Post(post))), post);

    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}