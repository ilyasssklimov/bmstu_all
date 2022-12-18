#include "model_bl/comment.h"


std::string CommentBL::get_date()
{
    return _date;
}


std::string CommentBL::get_text()
{
    return _text;
}


int CommentBL::get_author_id() const
{
    return _author_id;
}


int CommentBL::get_post_id() const
{
    return _post_id;
}