#pragma once

#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include "model_bl/comment.h"
#include "model_dto/user.h"


#include OATPP_CODEGEN_BEGIN(DTO)  // =============================================================

class CommentOatpp: public oatpp::DTO 
{  
    DTO_INIT(CommentOatpp, DTO)

    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, date);
    DTO_FIELD(String, text);
    DTO_FIELD(Object<UserOatpp>, author);
};

class CommentsOatpp: public oatpp::DTO 
{  
    DTO_INIT(CommentsOatpp, DTO)
    DTO_FIELD(List<Object<CommentOatpp>>, comments);
};

class NewCommentOatpp: public oatpp::DTO
{
    DTO_INIT(NewCommentOatpp, DTO)

    DTO_FIELD(String, text);
};


#include OATPP_CODEGEN_END(DTO)  // ===============================================================


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

    oatpp::Object<CommentOatpp> get_oatpp_object();
    static oatpp::Object<CommentsOatpp> get_oatpp_comments(std::vector<CommentDTO> comments_dto);

    explicit operator bool() const { return !_date.empty(); }
    
    bool operator == (CommentDTO comment) const
    {
        return comment.get_id() == _id;
    }

private:
    int _id;
    std::string _date;
    std::string _text;
    int _post_id;
    UserDTO _author;
};
