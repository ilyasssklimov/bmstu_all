#ifndef TEST_COMMENT_REPOSITORY_H
#define TEST_COMMENT_REPOSITORY_H

#include <algorithm>
#include "controller/client.h"


class CommentRepository: public ICommentRepository
{
public:
    CommentRepository(std::vector<CommentBL> comments): _comments(comments) {}

    CommentBL get_comment(int comment_id) override
    {
        return _comments[comment_id];
    }

    std::vector<CommentBL> get_comments(int post_id) override
    {
        std::vector<CommentBL> comments;
        for (auto &comment: _comments)
        {
            if (comment.get_post_id() == post_id)
                comments.push_back(comment);
        }

        return comments;
    }

    int get_comment_id(CommentBL comment) override
    {
        return std::distance(_comments.begin(), std::find(_comments.begin(), _comments.end(), comment));
    }

    CommentBL add_comment(std::string date, std::string text, int author_id, int post_id) override
    {
        CommentBL comment(date, text, author_id, post_id);
        _comments.push_back(comment);
        return comment;
    }

    CommentBL delete_comment(int comment_id) override
    {
        CommentBL comment = _comments[comment_id];
        _comments.erase(_comments.begin() + comment_id);
        return comment;
    }

    CommentBL update_comment(int comment_id, std::string date, std::string text) override
    {
        CommentBL comment = _comments[comment_id];

        std::string upd_date;
        if (!date.empty())
            upd_date = date;
        else
            upd_date = comment.get_date();

        std::string upd_text;
        if (!text.empty())
            upd_text = text;
        else
            upd_text = comment.get_text();

        CommentBL upd_comment(upd_date, upd_text, comment.get_author_id(), comment.get_post_id());

        _comments[comment_id] = upd_comment;
        return upd_comment;
    }

private:
    std::vector<CommentBL> _comments;
};


#endif  // TEST_COMMENT_REPOSITORY_H
