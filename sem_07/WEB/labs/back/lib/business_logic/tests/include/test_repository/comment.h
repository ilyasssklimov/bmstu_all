#pragma once

#include <algorithm>
#include "service/client.h"


class TestCommentRepository: public ICommentRepository
{
public:
    TestCommentRepository(std::vector<CommentBL> comments): _comments(comments) {}

    CommentBL get_comment(int comment_id) override;
    std::vector<CommentBL> get_comments(int post_id) override;
    int get_comment_id(CommentBL comment) override;

    CommentBL add_comment(std::string date, std::string text, int author_id, int post_id) override;
    CommentBL delete_comment(int comment_id) override;
    CommentBL update_comment(int comment_id, std::string date, std::string text) override;

private:
    std::vector<CommentBL> _comments;
};
