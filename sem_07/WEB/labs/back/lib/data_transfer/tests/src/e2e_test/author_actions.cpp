#include <gtest/gtest.h>

#include "service/guest.h"
#include "service/author.h"
#include "service/admin.h"

#include "controller/guest.hpp"
#include "controller/author.hpp"
#include "controller/admin.hpp"

#include "database/pg_database_async.h"
#include "repository/user.h"
#include "repository/post.h"
#include "repository/comment.h"

#include "locator.hpp"
#include "builder/user.h"
#include "builder/post.h"
#include "builder/comment.h"


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

    ServiceLocator::instantiate<AdminService>();
    ServiceLocator::instantiate<AdminController>();

    auto guest_controller = ServiceLocator::resolve<GuestController>();
    auto author_controller = ServiceLocator::resolve<AuthorController>();
    auto admin_controller = ServiceLocator::resolve<AdminController>();

    UserBL user = UserBuilder()
                  .with_name("Илья")
                  .with_surname("Климов")
                  .with_login("ilyasssklimov")
                  .with_password("password")
                  .with_city("Якутск")
                  .with_access("A")
                  .build(false);

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
        user.get_name(),
        user.get_surname(),
        user.get_login(),
        user.get_password(),
        user.get_city(),
        user.get_access()
    );

    // Assert
    EXPECT_TRUE((bool) new_user);
    EXPECT_EQ(guest_controller->get_users().size(), 1);
    EXPECT_EQ(guest_controller->get_users()[0], UserDTO(db->get_user_id(user.get_login()), user));

    // Instead of authorization
    int user_id = db->get_user_id(user.get_login());

    // Get posts
    // Arrange    
    PostBL post = PostBuilder()
                  .with_name("Новое мероприятие")
                  .with_author_id(user_id)
                  .with_information("Некоторая информация про пост")
                  .with_city("Москва")
                  .with_organizer("https://bmstu.ru")
                  .with_date("01.01.2023")
                  .with_visible(false)
                  .build(false);

    // Act
    auto new_post = author_controller->create_post(
        user_id,
        post.get_name(),
        post.get_information(),
        post.get_city(),
        post.get_organizer(),
        post.get_date()
    );

    // Assert
    EXPECT_EQ(new_post, FullPostDTO(
        db->get_post_id(Post(post)),
        UserDTO(user_id, user),
        post,
        {}
    ));

    // Submit post
    // Arrange
    int post_id = db->get_post_id(Post(post));

    // Act
    admin_controller->submit_post(post_id);

    // Assert
    EXPECT_EQ(author_controller->get_posts().size(), 1);
    EXPECT_EQ(author_controller->get_posts()[0], PostDTO(
        db->get_post_id(Post(post)),
        UserDTO(user_id, user),
        post
    ));

    // Add comment to post
    // Arrange
    CommentBL comment = CommentBuilder()
                        .with_date("02.01.2023")
                        .with_text("Классное мероприятие")
                        .with_author_id(user_id)
                        .with_post_id(post_id)
                        .build(false);

    // Act
    auto new_comment = author_controller->add_comment(
        comment.get_date(),
        comment.get_text(),
        comment.get_author_id(),
        comment.get_post_id()
    );
    
    // Assert
    EXPECT_EQ(new_comment, CommentDTO(
        db->get_comment_id(Comment(comment)),
        comment, 
        UserDTO(user_id, user)
    ));
    EXPECT_EQ(author_controller->get_full_post(post_id).get_comments().size(), 1);
    EXPECT_EQ(author_controller->get_full_post(post_id).get_comments()[0], CommentDTO(
        db->get_comment_id(Comment(comment)),
        comment, 
        UserDTO(user_id, user)
    ));

    db->delete_comments();
    db->delete_posts();
    db->delete_users();
}