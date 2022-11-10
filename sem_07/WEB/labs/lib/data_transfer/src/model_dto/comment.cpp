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