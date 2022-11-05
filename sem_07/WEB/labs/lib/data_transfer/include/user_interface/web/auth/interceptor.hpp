#pragma once

#include "handler.hpp"

#include "oatpp/web/server/interceptor/RequestInterceptor.hpp"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/handler/AuthorizationHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"


class AuthInterceptor : public oatpp::web::server::interceptor::RequestInterceptor
{
public:
    AuthInterceptor(const std::shared_ptr<JWT>& jwt);
    std::shared_ptr<OutgoingResponse> intercept(const std::shared_ptr<IncomingRequest>& request) override;

private:
    AuthHandler _auth_handler;
    oatpp::web::server::HttpRouterTemplate<bool> _auth_endpoints;
};
