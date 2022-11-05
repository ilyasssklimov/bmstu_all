#pragma once

#include <vector>
#include "model_bl/comment.h"


class ICommentRepository
{
public:
    virtual CommentBL get_comment(int comment_id) = 0;
    virtual int get_comment_id(CommentBL comment) = 0;
    virtual std::vector<CommentBL> get_comments(int post_id) = 0;
    virtual CommentBL add_comment(std::string date, std::string text, int author_id, int post_id) = 0;
    virtual CommentBL delete_comment(int comment_id) = 0;
    virtual CommentBL update_comment(int comment_id, std::string date, std::string text) = 0;
};
