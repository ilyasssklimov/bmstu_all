#include "user_interface/web/auth/handler.hpp"


std::shared_ptr<AuthHandler::AuthorizationObject> AuthHandler::authorize(const oatpp::String& token) 
{
  return _jwt->readAndVerifyToken(token);
}
