#include <algorithm>
#include "test_repository/comment.h"


CommentBL CommentRepository::get_comment(int comment_id)
{
    return _comments[comment_id];
}


std::vector<CommentBL> CommentRepository::get_comments(int post_id)
{
    std::vector<CommentBL> comments;

    for (auto &comment: _comments)
    {
        if (comment.get_post_id() == post_id)
            comments.push_back(comment);
    }

    return comments;
}


int CommentRepository::get_comment_id(CommentBL comment)
{
    return std::distance(_comments.begin(), std::find(_comments.begin(), _comments.end(), comment));
}


CommentBL CommentRepository::add_comment(std::string date, std::string text, int author_id, int post_id)
{
    CommentBL comment(date, text, author_id, post_id);
    _comments.push_back(comment);
    return comment;
}


CommentBL CommentRepository::delete_comment(int comment_id)
{
    CommentBL comment = _comments[comment_id];
    _comments.erase(_comments.begin() + comment_id);
    return comment;
}


CommentBL CommentRepository::update_comment(int comment_id, std::string date, std::string text)
{
    CommentBL comment = _comments[comment_id];

    std::string upd_date = date.empty() ? comment.get_date() : date;
    std::string upd_text = text.empty() ? comment.get_text() : text;

    CommentBL upd_comment(upd_date, upd_text, comment.get_author_id(), comment.get_post_id());

    _comments[comment_id] = upd_comment;
    return upd_comment;
}
