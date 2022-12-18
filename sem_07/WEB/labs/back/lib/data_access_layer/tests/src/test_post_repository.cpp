#include <gtest/gtest.h>
#include "../../data_access_layer/include/database/pg_database.h"
#include "../../data_access_layer/include/repository/post.h"
#include "logger.h"


TEST(REPOSITORY_POST_TEST, GET_ADD_POST)
{
    PGDatabase db(PGDatabaseParams);
    PostRepository post_repo(&db);

    PostBL adding_post = post_repo.add_post("name_11", 1, "info_1", "city_1", "organizer_1", "date_1");
    PostBL post("name_11", 1, "info_1", "city_1","organizer_1", "date_1", false);

    post_repo.delete_post(post_repo.get_post_id(adding_post));
    EXPECT_EQ(adding_post, post);
}


TEST(REPOSITORY_POST_TEST, DELETE_POST)
{
    PGDatabase db(PGDatabaseParams);
    PostRepository post_repo(&db);

    post_repo.add_post("name_1", 1, "info_1",
                       "city_1", "organizer_1", "date_1");
    PostBL post("name_1", 1, "info_1", "city_1","organizer_1", "date_1", false);

    PostBL deleting_post = post_repo.delete_post(post_repo.get_post_id(post));
    EXPECT_EQ(deleting_post, post);
}


TEST(REPOSITORY_POST_TEST, GET_POSTS)
{
    PGDatabase db(PGDatabaseParams);
    PostRepository post_repo(&db);

    post_repo.add_post("name_1", 1, "info_1",
                       "city_1", "organizer_1", "date_1");
    post_repo.add_post("name_2", 1, "info_2",
                       "city_2", "organizer_2", "date_2");

    PostBL post_1("name_1", 1, "info_1","city_1","organizer_1", "date_1", true);
    PostBL post_2("name_2", 1, "info_2","city_2","organizer_2", "date_2", true);

    post_repo.update_post(post_repo.get_post_id(post_1), "", "", "", "", true);
    post_repo.update_post(post_repo.get_post_id(post_2), "", "", "", "", true);

    std::vector<PostBL> posts = post_repo.get_posts();
    EXPECT_EQ(posts[posts.size() - 2], post_1);
    EXPECT_EQ(posts[posts.size() - 1], post_2);

    post_repo.delete_post(post_repo.get_post_id(post_1));
    post_repo.delete_post(post_repo.get_post_id(post_2));
}


TEST(REPOSITORY_POST_TEST, UPDATE_POST)
{
    PGDatabase db(PGDatabaseParams);
    PostRepository post_repo(&db);

    post_repo.add_post("name_1", 1, "info_1",
                       "city_1","organizer_1", "date_1");

    PostBL post("name_1", 1, "info_1","city_1","organizer_1", "date_1", false);
    PostBL upd_post("name_1", 1, "info_1_upd", "city_1", "organizer_1", "date_1_upd", false);

    PostBL updating_post = post_repo.update_post(post_repo.get_post_id(post), "", "info_1_upd",
                                                 "", "date_1_upd", false);

    EXPECT_EQ(updating_post, upd_post);
    post_repo.delete_post(post_repo.get_post_id(upd_post));
}
