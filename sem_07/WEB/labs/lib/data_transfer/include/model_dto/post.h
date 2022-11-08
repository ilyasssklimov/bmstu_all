#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "model_bl/post.h"
#include "model_dto/user.h"
#include "model_dto/comment.h"


class PostDTO
{
public:
    PostDTO(int id, std::string name, UserDTO author, std::string information, std::string city, std::string date):
        _id(id), _name(std::move(name)), _author(author), _information(std::move(information)),
        _city(std::move(city)), _date(std::move(date)) {}

    PostDTO(int post_id, UserDTO author, PostBL post_bl);
    PostDTO() = default;

    int get_id();
    std::string get_name();
    UserDTO get_author();
    std::string get_information();
    std::string get_city();
    std::string get_date();

    explicit operator bool() const { return !_name.empty(); }
    bool operator == (PostDTO post) const
    {
        return post.get_id() == _id;
    }

protected:
    int _id;
    std::string _name;
    UserDTO _author;
    std::string _information;
    std::string _city;
    std::string _date;
};


class FullPostDTO: public PostDTO
{
public:
    FullPostDTO(int id, std::string name, UserDTO author, std::string information, std::string city, 
            std::string organizer, std::string date, std::vector<CommentDTO> comments):
        PostDTO(id, name, author, information, city, date), 
        _organizer(std::move(organizer)), _comments(std::move(comments)) {}

    FullPostDTO(int post_id, UserDTO author, PostBL post_bl, std::vector<CommentDTO> comments);
    FullPostDTO() = default;

    std::string get_organizer();
    std::vector<CommentDTO> get_comments();

    explicit operator bool() const { return !_name.empty(); }
    bool operator == (FullPostDTO post) const
    {
        return post.get_id() == _id;
    }

protected:
    std::string _organizer;
    std::vector<CommentDTO> _comments;
};
