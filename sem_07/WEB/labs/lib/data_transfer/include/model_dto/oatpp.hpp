#pragma once

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"


#include OATPP_CODEGEN_BEGIN(DTO)  // =============================================================



class UpdUserOatpp: public oatpp::DTO 
{  
    DTO_INIT(UpdUserOatpp, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD(String, surname);
    DTO_FIELD(String, login);
    DTO_FIELD(String, password);
    DTO_FIELD(String, city);
};


class NewCommentOatpp: public oatpp::DTO
{
    DTO_INIT(NewCommentOatpp, DTO)

    DTO_FIELD(String, text);
};





class PostFilters: public oatpp::DTO
{
    DTO_INIT(PostFilters, DTO)

    DTO_FIELD(String, date);
    DTO_FIELD(String, name);
    DTO_FIELD(String, city);
    DTO_FIELD(String, author);
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
