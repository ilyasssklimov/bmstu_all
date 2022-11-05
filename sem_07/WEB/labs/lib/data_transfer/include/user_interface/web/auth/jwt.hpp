#pragma once

#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/core/Types.hpp"
#include <jwt-cpp/jwt.h>


class JWT 
{
public:
	struct Payload: public oatpp::web::server::handler::AuthorizationObject 
	{
    	oatpp::String user_id;
    };
	
	JWT(const oatpp::String& secret, const oatpp::String& issuer);
	oatpp::String createToken(const std::shared_ptr<Payload>& payload);
	std::shared_ptr<Payload> readAndVerifyToken(const oatpp::String& token);

private:
 	oatpp::String _secret, _issuer;
  	jwt::verifier<jwt::default_clock, jwt::traits::kazuho_picojson> _verifier;
};
