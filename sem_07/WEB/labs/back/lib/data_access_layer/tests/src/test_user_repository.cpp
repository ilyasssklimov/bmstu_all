#include <gtest/gtest.h>
#include "database/pg_database.h"
#include "repository/user.h"


TEST(REPOSITORY_USER_TEST, GET_ADD_USER)
{
    PGDatabase db(PGDatabaseParams);
    UserRepository user_repo(&db);
    UserBL adding_user = user_repo.add_user("test_name_1", "test_surname_1","test_login_1",
                                            "test_password_1", "test_city_1", "U");

    UserBL user("test_name_1", "test_surname_1","test_login_1",
                "test_password_1", "test_city_1", "U");

    user_repo.delete_user(user_repo.get_user_id(adding_user));
    EXPECT_EQ(adding_user, user);
}


TEST(REPOSITORY_USER_TEST, DELETE_USER)
{
    PGDatabase db(PGDatabaseParams);
    UserRepository user_repo(&db);

    user_repo.add_user("test_name_2", "test_surname_2","test_login_2",
    "test_password_2", "test_city_2", "U");
    UserBL user("test_name_2", "test_surname_2","test_login_2",
                "test_password_2", "test_city_2", "U");

    UserBL deleting_user = user_repo.delete_user(user_repo.get_user_id(user));
    EXPECT_EQ(deleting_user, user);
}


TEST(REPOSITORY_USER_TEST, CHECK_USER)
{
    PGDatabase db(PGDatabaseParams);
    UserRepository user_repo(&db);

    user_repo.add_user("test_name_2", "test_surname_2","test_login_2",
    "test_password_2", "test_city_2", "U");
    UserBL user("test_name_2", "test_surname_2","test_login_2",
                "test_password_2", "test_city_2", "U");

    EXPECT_TRUE(user_repo.check_user(user.get_login(), user.get_password()));
    user_repo.delete_user(user_repo.get_user_id(user));
    EXPECT_FALSE(user_repo.check_user(user.get_login(), user.get_password()));
}


TEST(REPOSITORY_USER_TEST, GET_USERS)
{
    PGDatabase db(PGDatabaseParams);
    UserRepository user_repo(&db);

    user_repo.add_user("test_name_1", "test_surname_1","test_login_1",
    "test_password_1", "test_city_1", "U");
    user_repo.add_user("test_name_2", "test_surname_2","test_login_2",
    "test_password_2", "test_city_2", "U");

    UserBL user_1("test_name_1", "test_surname_1","test_login_1",
                  "test_password_1", "test_city_1", "U");
    UserBL user_2("test_name_2", "test_surname_2","test_login_2",
                "test_password_2", "test_city_2", "U");

    std::vector<UserBL> users = user_repo.get_users();
    EXPECT_EQ(users[users.size() - 2], user_1);
    EXPECT_EQ(users[users.size() - 1], user_2);

    user_repo.delete_user(user_repo.get_user_id(user_1));
    user_repo.delete_user(user_repo.get_user_id(user_2));
}


TEST(REPOSITORY_USER_TEST, UPDATE_USER)
{
    PGDatabase db(PGDatabaseParams);
    UserRepository user_repo(&db);

    user_repo.add_user("test_name_1", "test_surname_1","test_login_1",
    "test_password_1", "test_city_1", "U");

    UserBL user("test_name_1", "test_surname_1","test_login_1",
                "test_password_1", "test_city_1", "U");
    UserBL upd_user("test_name_1", "test_surname_upd","test_login_1",
                "test_password_upd", "test_city_1", "U");

    UserBL updating_user = user_repo.update_user(user_repo.get_user_id(user), "", "test_surname_upd", "",
                                                 "test_password_upd", "", {}, false);

    EXPECT_EQ(updating_user, upd_user);
    user_repo.delete_user(user_repo.get_user_id(upd_user));
}
