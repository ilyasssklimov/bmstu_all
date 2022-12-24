#pragma once

#include "model_bl/comment.h"


class CommentBuilder 
{
public:
    explicit CommentBuilder();
    CommentBL build(bool random=true);

    CommentBuilder with_date(std::string name);
    CommentBuilder with_text(std::string text);
    CommentBuilder with_author_id(int author_id);
    CommentBuilder with_post_id(int post_id);

private:
    std::string _date = ".12.2022";
    std::string _text = "text_";
    int _author_id = 0;
    int _post_id = 0;

    std::string get_random(int range=10);
};