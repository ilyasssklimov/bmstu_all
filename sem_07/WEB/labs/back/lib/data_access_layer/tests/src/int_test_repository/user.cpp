#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "database/pg_database_async.h"
#include "repository/user.h"

#include "builder/user.h"
#include "locator.hpp"


std::unordered_map<size_t, std::shared_ptr<void>> ServiceLocator::_instances;

TEST(REPOSITORY_USER_INT_TEST, ADD_USER)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    auto user_repo = std::make_shared<UserRepository>(db);

    // Act
    UserBL add_user = user_repo->add_user(
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

    db->delete_users();
}


TEST(REPOSITORY_USER_INT_TEST, GET_USER_ID)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);

    int user_id = db->get_user_id(user.get_login());
    auto user_repo = std::make_shared<UserRepository>(db);

    // Act
    int get_user_id = user_repo->get_user_id(user);

    // Assert
    EXPECT_EQ(get_user_id, user_id);

    db->delete_users();
}


TEST(REPOSITORY_USER_INT_TEST, GET_USER)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);

    int user_id = db->get_user_id(user.get_login());
    auto user_repo = std::make_shared<UserRepository>(db);

    // Act
    UserBL get_user = user_repo->get_user(user_id);

    // Assert
    EXPECT_EQ(get_user, user);

    db->delete_users();
}


TEST(REPOSITORY_USER_INT_TEST, CHECK_USER)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);

    auto user_repo = std::make_shared<UserRepository>(db);

    // Act
    UserBL get_user = user_repo->check_user(user.get_login(), user.get_password());
    UserBL fake_user = user_repo->check_user("fake_login", "fake_password");

    // Assert
    EXPECT_EQ(get_user, user);
    EXPECT_EQ(fake_user, UserBL());

    db->delete_users();
}


TEST(REPOSITORY_USER_INT_TEST, GET_USERS)
{
    // Arrange
    auto builder = UserBuilder();
    UserBL user_1 = builder.with_login("login_1").build(false);
    UserBL user_2 = builder.with_login("login_2").build(false);

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user_1);
    add_user_to_db(db, user_2);

    auto user_repo = std::make_shared<UserRepository>(db);

    // Act
    std::vector<UserBL> get_users = user_repo->get_users();

    // Assert
    EXPECT_EQ(get_users.size(), 2);
    EXPECT_EQ(get_users[0], user_1);
    EXPECT_EQ(get_users[1], user_2);

    db->delete_users();
}


TEST(REPOSITORY_USER_INT_TEST, DELETE_USER)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);

    int user_id = db->get_user_id(user.get_login());
    auto user_repo = std::make_shared<UserRepository>(db);

    // Act
    UserBL del_user = user_repo->delete_user(user_id);

    // Assert
    EXPECT_EQ(del_user, user);
    EXPECT_EQ(user_repo->get_users().size(), 0);

    db->delete_users();
}


TEST(REPOSITORY_USER_INT_TEST, UPDATE_USER)
{
    // Arrange
    UserBL user = UserBuilder().build();
    std::string new_name = "new_name";

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);

    int user_id = db->get_user_id(user.get_login());
    auto user_repo = std::make_shared<UserRepository>(db);

    // Act
    UserBL upd_user = user_repo->update_user(user_id, new_name, "", "", "", "");

    // Assert
    EXPECT_EQ(upd_user.get_name(), new_name);
    EXPECT_EQ(user_repo->get_users()[0].get_name(), new_name);

    db->delete_users();
}
