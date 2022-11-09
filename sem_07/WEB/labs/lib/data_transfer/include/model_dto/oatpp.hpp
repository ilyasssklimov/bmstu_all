#pragma once

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)  // =============================================================

class AuthOatpp: public oatpp::DTO
{
    DTO_INIT(AuthOatpp, DTO)

    DTO_FIELD(String, token);
};


class AuthUserOatpp: public oatpp::DTO
{
    DTO_INIT(AuthUserOatpp, DTO)
    
    DTO_FIELD(String, login);
    DTO_FIELD(String, password);
};


class UserOatpp: public oatpp::DTO 
{  
    DTO_INIT(UserOatpp, DTO)

    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, full_name);
    DTO_FIELD(String, login);
    DTO_FIELD(String, city);
    DTO_FIELD(String, access);
};

class NewUserOatpp: public oatpp::DTO 
{  
    DTO_INIT(NewUserOatpp, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD(String, surname);
    DTO_FIELD(String, login);
    DTO_FIELD(String, password);
    DTO_FIELD(String, city);
    DTO_FIELD(String, access);
};

class UsersOatpp: public oatpp::DTO 
{  
    DTO_INIT(UsersOatpp, DTO)
    DTO_FIELD(List<Object<UserOatpp>>, users);
};


class CommentOatpp: public oatpp::DTO 
{  
    DTO_INIT(CommentOatpp, DTO)

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


class PostOatpp: public oatpp::DTO 
{  
    DTO_INIT(PostOatpp, DTO)

    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, name);
    DTO_FIELD(Object<UserOatpp>, author);
    DTO_FIELD(String, information);
    DTO_FIELD(String, city);
    DTO_FIELD(String, date);
};

class PostsOatpp: public oatpp::DTO 
{  
    DTO_INIT(PostsOatpp, DTO)
    DTO_FIELD(List<Object<PostOatpp>>, posts);
};

class FullPostOatpp: public oatpp::DTO
{
    DTO_INIT(FullPostOatpp, DTO)

    DTO_FIELD(UInt32, id);
    DTO_FIELD(String, name);
    DTO_FIELD(Object<UserOatpp>, author);
    DTO_FIELD(String, information);
    DTO_FIELD(String, organizer);
    DTO_FIELD(String, city);
    DTO_FIELD(String, date);
    DTO_FIELD(List<Object<CommentOatpp>>, comments);
};

class FullPostsOatpp: public oatpp::DTO 
{  
    DTO_INIT(FullPostsOatpp, DTO)
    DTO_FIELD(List<Object<FullPostOatpp>>, posts);
};

class PostFilters: public oatpp::DTO
{
    DTO_INIT(PostFilters, DTO)

    DTO_FIELD(String, date);
    DTO_FIELD(String, name);
    DTO_FIELD(String, city);
    DTO_FIELD(String, author);
};

#include OATPP_CODEGEN_END(DTO)  // ===============================================================
