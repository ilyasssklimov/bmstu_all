#include "model_dto/comment.h"


CommentDTO::CommentDTO(int comment_id, CommentBL comment_bl, UserDTO author)
{
    _id = comment_id;
    _date = comment_bl.get_date();
    _text = comment_bl.get_text();
    _post_id = comment_bl.get_post_id();
    _author = author;
}


int CommentDTO::get_id()
{
    return _id;
}


std::string CommentDTO::get_date()
{
    return _date;
}


std::string CommentDTO::get_text()
{
    return _text;
}


int CommentDTO::get_post_id()
{
    return _post_id;
}


UserDTO CommentDTO::get_author()
{
    return _author;
}


oatpp::Object<CommentOatpp> CommentDTO::get_oatpp_object()
{
    auto comment = CommentOatpp::createShared(); 

    comment->id = get_id(); 
    comment->date = get_date();
    comment->text = get_text();
    comment->author = get_author().get_oatpp_object();

    return comment;
}


oatpp::Object<CommentsOatpp> CommentDTO::get_oatpp_comments(std::vector<CommentDTO> comments_dto)
{
    auto comments = CommentsOatpp::createShared();
    comments->comments = {};

    for (auto& comment_dto: comments_dto)
    {
        auto comment = comment_dto.get_oatpp_object();
        comments->comments->push_back(comment);
    }

    return comments;
}


