#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "mock_database/database.h"
#include "repository/user.h"
#include "builder/user.h"
#include "locator.hpp"


std::unordered_map<size_t, std::shared_ptr<void>> ServiceLocator::_instances;

TEST(REPOSITORY_USER_TEST, ADD_USER)
{
    // Arrange
    auto mock_db = new MockDatabase();
    UserBL user = UserBuilder().build();

    EXPECT_CALL(*mock_db, add_user(
        user.get_name(),
        user.get_surname(),
        user.get_login(),
        user.get_password(),
        user.get_city(),
        user.get_access()
    )).WillOnce(testing::Return(User(user)));
    
    auto user_repo = UserRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    UserBL add_user = user_repo.add_user(
        user.get_name(),
        user.get_surname(),
        user.get_login(),
        user.get_password(),
        user.get_city(),
        user.get_access()
    );

    // Assert
    EXPECT_EQ(add_user, user);
}


TEST(REPOSITORY_USER_TEST, GET_USER_ID)
{
    // Arrange
    auto mock_db = new MockDatabase();
    UserBL user = UserBuilder().build();
    int user_id = 0;

    EXPECT_CALL(*mock_db, get_user_id(user.get_login())).WillOnce(testing::Return(user_id));
    
    auto user_repo = UserRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    int get_user_id = user_repo.get_user_id(user);

    // Assert
    EXPECT_EQ(get_user_id, user_id);
}


TEST(REPOSITORY_USER_TEST, GET_USER)
{
    // Arrange
    auto mock_db = new MockDatabase();
    int user_id = 0;
    UserBL user = UserBuilder().build();

    EXPECT_CALL(*mock_db, get_user(user_id)).WillOnce(testing::Return(user));
    
    auto user_repo = UserRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    UserBL get_user = user_repo.get_user(user_id);

    // Assert
    EXPECT_EQ(get_user, user);
}


TEST(REPOSITORY_USER_TEST, CHECK_USER)
{
    // Arrange
    auto mock_db = new MockDatabase();
    UserBL user = UserBuilder().build();
    std::string login = user.get_login();
    std::string password = user.get_password();

    EXPECT_CALL(*mock_db, get_user(login, password)).WillOnce(testing::Return(user));
    
    auto user_repo = UserRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    UserBL get_user = user_repo.check_user(login, password);

    // Assert
    EXPECT_EQ(get_user, user);
}


TEST(REPOSITORY_USER_TEST, GET_USERS)
{
    // Arrange
    auto mock_db = new MockDatabase();
    auto builder = UserBuilder();
    std::vector<UserBL> users_bl = { builder.build(), builder.build() };
    std::vector<User> users = { User(users_bl[0]), User(users_bl[1]) };

    EXPECT_CALL(*mock_db, get_users()).WillOnce(testing::Return(users));
    
    auto user_repo = UserRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    std::vector<UserBL> get_users = user_repo.get_users();

    // Assert
    EXPECT_EQ(get_users, users_bl);
}


TEST(REPOSITORY_USER_TEST, DELETE_USER)
{
    // Arrange
    auto mock_db = new MockDatabase();
    UserBL user = UserBuilder().build();
    int user_id = 0;

    EXPECT_CALL(*mock_db, delete_user(user_id)).WillOnce(testing::Return(user));
    
    auto user_repo = UserRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    UserBL del_user = user_repo.delete_user(user_id);

    // Assert
    EXPECT_EQ(del_user, user);
}


TEST(REPOSITORY_USER_TEST, UPDATE_USER)
{
    // Arrange
    auto mock_db = new MockDatabase();
    std::string new_name = "new_name";

    auto builder = UserBuilder();
    UserBL user = builder.build();
    UserBL new_user = builder.with_name(new_name).build(false);
    int user_id = 0;

    EXPECT_CALL(*mock_db, update_user(
        user_id,
        new_name,
        user.get_surname(),
        user.get_login(),
        user.get_password(),
        user.get_city()
    )).WillOnce(testing::Return(new_user));
    
    EXPECT_CALL(*mock_db, get_user(user_id)).WillOnce(testing::Return(user));
    
    auto user_repo = UserRepository(std::shared_ptr<MockDatabase>(mock_db));

    // Act
    UserBL upd_user = user_repo.update_user(user_id, new_name, "", "", "", "");

    // Assert
    EXPECT_EQ(upd_user, new_user);
}
