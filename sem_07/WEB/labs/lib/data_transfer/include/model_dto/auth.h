#pragma once

#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"


class BearerAuthObject: public oatpp::web::server::handler::AuthorizationObject 
{
public:
	oatpp::UInt32 id;
	oatpp::String access;
	oatpp::String token;
};


#include OATPP_CODEGEN_BEGIN(DTO)  // =============================================================

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

#include OATPP_CODEGEN_END(DTO)  // ===============================================================
