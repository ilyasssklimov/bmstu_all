#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "model_bl/post.h"
#include "model_dto/user.h"
#include "model_dto/comment.h"


#include OATPP_CODEGEN_BEGIN(DTO)  // =============================================================

class PreviewOatpp: public oatpp::DTO 
{  
    DTO_INIT(PreviewOatpp, DTO)

    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, name);
    DTO_FIELD(Object<UserOatpp>, author);
    DTO_FIELD(String, information);
    DTO_FIELD(String, city);
    DTO_FIELD(String, date);
};

class PreviewsOatpp: public oatpp::DTO 
{  
    DTO_INIT(PreviewsOatpp, DTO)
    DTO_FIELD(List<Object<PreviewOatpp>>, previews);
};


class PostOatpp: public oatpp::DTO
{
    DTO_INIT(PostOatpp, DTO)

    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, name);
    DTO_FIELD(Object<UserOatpp>, author);
    DTO_FIELD(String, information);
    DTO_FIELD(String, organizer);
    DTO_FIELD(String, city);
    DTO_FIELD(String, date);
    DTO_FIELD(Object<CommentsOatpp>, comments);
};

class PostsOatpp: public oatpp::DTO 
{  
    DTO_INIT(PostsOatpp, DTO)
    DTO_FIELD(List<Object<PostOatpp>>, posts);
};


class NewPostOatpp: public oatpp::DTO
{
    DTO_INIT(NewPostOatpp, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD(String, information);
    DTO_FIELD(String, city);
    DTO_FIELD(String, organizer);
};

class UpdPostOatpp: public oatpp::DTO
{
    DTO_INIT(UpdPostOatpp, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD(String, information);
    DTO_FIELD(String, city);
    DTO_FIELD(String, date);
};

#include OATPP_CODEGEN_END(DTO)  // ===============================================================


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

    oatpp::Object<PreviewOatpp> get_oatpp_object();
    static oatpp::Object<PreviewsOatpp> get_oatpp_previews(std::vector<PostDTO> posts_dto);

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

    oatpp::Object<PostOatpp> get_oatpp_object();
    static oatpp::Object<PostsOatpp> get_oatpp_posts(std::vector<FullPostDTO> posts_dto);

    explicit operator bool() const { return !_name.empty(); }
    bool operator == (FullPostDTO post) const
    {
        return post.get_id() == _id;
    }

protected:
    std::string _organizer;
    std::vector<CommentDTO> _comments;
};
