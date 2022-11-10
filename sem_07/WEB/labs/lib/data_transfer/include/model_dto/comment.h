#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "model_bl/comment.h"
#include "model_dto/user.h"


class CommentDTO
{
public:
    CommentDTO(int id, std::string date, std::string text, int post_id, UserDTO author): 
        _id(id), _date(std::move(date)), _text(std::move(text)), _post_id(post_id), _author(author) {};
    CommentDTO(int comment_id, CommentBL comment_bl, UserDTO author);
    CommentDTO() = default;

    int get_id();
    std::string get_date();
    std::string get_text();
    int get_post_id();
    UserDTO get_author();

    explicit operator bool() const { return !_date.empty(); }

private:
    int _id;
    std::string _date;
    std::string _text;
    int _post_id;
    UserDTO _author;
};
