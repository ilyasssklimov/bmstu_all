#include <gtest/gtest.h>

#include "service/auth.h"
#include "builder/user.h"

#include "database/pg_database_async.h"
#include "repository/user.h"


TEST(SERVICE_AUTH_INT_TEST, GET_PASSWORD)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    auto user_repo = std::make_shared<UserRepository>(db);
    auto service = AuthService(user_repo);

    // Act
    std::string password = service.get_password(user_id);

    // Assert
    EXPECT_EQ(password, user.get_password());

    db->delete_users();
}


TEST(SERVICE_AUTH_INT_TEST, GET_ACCESS)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    auto user_repo = std::make_shared<UserRepository>(db);
    auto service = AuthService(user_repo);

    // Act
    std::string access = service.get_access(user_id);

    // Assert
    EXPECT_EQ(access, user.get_access());

    db->delete_users();
}


TEST(SERVICE_AUTH_INT_TEST, GET_USER_ID)
{
    // Arrange
    UserBL user = UserBuilder().build();

    auto db = std::make_shared<PGDatabaseAsync>(PGDatabaseParams);
    add_user_to_db(db, user);
    int user_id = db->get_user_id(user.get_login());

    auto user_repo = std::make_shared<UserRepository>(db);
    auto service = AuthService(user_repo);

    // Act
    int get_user_id = service.get_user_id(user.get_login(), user.get_password());

    // Assert
    EXPECT_EQ(get_user_id, user_id);
    
    db->delete_users();
}
