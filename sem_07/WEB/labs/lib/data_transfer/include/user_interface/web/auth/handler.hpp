#pragma once

#include "jwt.hpp"


class AuthHandler: public oatpp::web::server::handler::BearerAuthorizationHandler 
{
public:
	AuthHandler(const std::shared_ptr<JWT>& jwt): 
 		oatpp::web::server::handler::BearerAuthorizationHandler("API"), _jwt(jwt) {}

	std::shared_ptr<AuthorizationObject> authorize(const oatpp::String& token) override;
	
private:
  std::shared_ptr<JWT> _jwt;
};
