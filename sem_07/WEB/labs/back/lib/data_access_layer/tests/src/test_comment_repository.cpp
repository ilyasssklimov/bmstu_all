#include <gtest/gtest.h>
#include "database/pg_database.h"
#include "repository/comment.h"


TEST(REPOSITORY_COMMENT_TEST, GET_ADD_COMMENT)
{
    PGDatabase db(PGDatabaseParams);
    CommentRepository comment_repo(&db);
    CommentBL adding_comment = comment_repo.add_comment("date_1", "text_1", 1, 1);

    CommentBL comment("date_1", "text_1", 1, 1);

    comment_repo.delete_comment(comment_repo.get_comment_id(adding_comment));
    EXPECT_EQ(adding_comment, comment);
}


TEST(REPOSITORY_COMMENT_TEST, DELETE_COMMENT)
{
    PGDatabase db(PGDatabaseParams);
    CommentRepository comment_repo(&db);

    comment_repo.add_comment("date_1", "text_1", 1, 1);
    CommentBL comment("date_1", "text_1", 1, 1);

    CommentBL deleting_comment = comment_repo.delete_comment(comment_repo.get_comment_id(comment));
    EXPECT_EQ(deleting_comment, comment);
}


TEST(REPOSITORY_COMMENT_TEST, UPDATE_COMMENT)
{
    PGDatabase db(PGDatabaseParams);
    CommentRepository comment_repo(&db);

    comment_repo.add_comment("date_1", "text_1", 1, 1);
    CommentBL comment("date_1", "text_1", 1, 1);
    CommentBL upd_comment("date_1", "text_1_upd", 1, 1);

    CommentBL updating_comment = comment_repo.update_comment(comment_repo.get_comment_id(comment),
                                                             "", "text_1_upd");

    EXPECT_EQ(updating_comment, upd_comment);
    comment_repo.delete_comment(comment_repo.get_comment_id(upd_comment));
}
