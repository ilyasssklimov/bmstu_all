#include "builder/comment.h"
#include <cstdlib>
#include <ctime>


CommentBuilder::CommentBuilder() 
{
    std::srand((unsigned) std::time(nullptr));
}


std::string CommentBuilder::get_random(int range)
{
    return std::to_string(std::rand() % range + 1);
}


CommentBL CommentBuilder::build(bool random) 
{
    if (random)
        return CommentBL(
            get_random(30) + _date,
            _text + get_random(),
            std::rand() % 10 + 1, 
            std::rand() % 10 + 1
        );

    return CommentBL(_date, _text, _author_id, _post_id);
}


CommentBuilder CommentBuilder::with_date(std::string date)
{
    _date = date;
    return *this;
}


CommentBuilder CommentBuilder::with_text(std::string text)
{
    _text = text;
    return *this;
}


CommentBuilder CommentBuilder::with_author_id(int author_id)
{
    _author_id = author_id;
    return *this;
}


CommentBuilder CommentBuilder::with_post_id(int post_id)
{
    _post_id = post_id;
    return *this;
}
