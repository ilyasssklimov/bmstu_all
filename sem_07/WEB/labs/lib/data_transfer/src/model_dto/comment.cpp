#include "model_dto/comment.h"


CommentDTO::CommentDTO(CommentBL comment_bl, UserDTO author)
{
    _date = comment_bl.get_date();
    _text = comment_bl.get_text();
    _author = author;
}


std::string CommentDTO::get_date()
{
    return _date;
}


std::string CommentDTO::get_text()
{
    return _text;
}


UserDTO CommentDTO::get_author()
{
    return _author;
}