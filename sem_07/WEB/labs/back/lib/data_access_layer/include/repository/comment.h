#pragma once

#include <memory>
#include "database/database.h"
#include "irepository/comment.h"


class CommentRepository: public ICommentRepository
{
public:
    explicit CommentRepository(std::shared_ptr<IDataBase> db): _db(db) {};
    explicit CommentRepository();

    CommentBL get_comment(int comment_id) override;
    int get_comment_id(CommentBL comment) override;
    std::vector<CommentBL> get_comments(int post_id) override;
    CommentBL add_comment(std::string date, std::string text, int author_id, int post_id) override;
    CommentBL delete_comment(int comment_id) override;
    CommentBL update_comment(int comment_id, std::string date, std::string text) override;

private:
    std::shared_ptr<IDataBase> _db;
    static CommentBL comment_to_comment_bl(Comment comment);
};
