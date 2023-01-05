#include <gtest/gtest.h>

#include "service/auth.h"
#include "builder/user.h"
#include "test_repository/user.h"


TEST(SERVICE_AUTH_TEST, GET_PASSWORD)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto user_repo = new TestUserRepository({ user });
    auto service = AuthService(std::shared_ptr<TestUserRepository>(user_repo));

    // Act
    std::string password = service.get_password(0);

    // Assert
    EXPECT_EQ(password, user.get_password());
}


TEST(SERVICE_AUTH_TEST, GET_ACCESS)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto user_repo = new TestUserRepository({ user });
    auto service = AuthService(std::shared_ptr<TestUserRepository>(user_repo));

    // Act
    std::string access = service.get_access(0);

    // Assert
    EXPECT_EQ(access, user.get_access());
}


TEST(SERVICE_AUTH_TEST, GET_USER_ID)
{
    // Arrange
    auto builder = UserBuilder();
    UserBL user_1 = builder.with_login("login_1").build(false);
    UserBL user_2 = builder.with_login("login_2").build(false);

    auto user_repo = new TestUserRepository({ user_1, user_2 });
    auto service = AuthService(std::shared_ptr<TestUserRepository>(user_repo));

    // Act
    int user_id = service.get_user_id(user_2.get_login(), user_2.get_password());

    // Assert
    EXPECT_EQ(user_id, 1);
}
