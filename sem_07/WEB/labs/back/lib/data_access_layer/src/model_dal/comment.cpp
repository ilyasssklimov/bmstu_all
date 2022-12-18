#include "model_dal/comment.h"


std::string Comment::get_date()
{
    return _date;
}


std::string Comment::get_text()
{
    return _text;
}


int Comment::get_author_id() const
{
    return _author_id;
}


int Comment::get_post_id() const
{
    return _post_id;
}


void Comment::set_date(const std::string &value)
{
    _date = value;
}


void Comment::set_text(const std::string &value)
{
    _text = value;
}
