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
    CommentDTO(std::string date, std::string text, UserDTO author): 
        _date(std::move(date)), _text(std::move(text)), _author(author) {};
    CommentDTO(CommentBL comment_bl, UserDTO author);
    CommentDTO() = default;

    std::string get_date();
    std::string get_text();
    UserDTO get_author();

    explicit operator bool() const { return !_date.empty(); }

private:
    std::string _date;
    std::string _text;
    UserDTO _author;
};
