#include "user_interface/web/auth/interceptor.hpp"


AuthInterceptor::AuthInterceptor(const std::shared_ptr<JWT>& jwt): _auth_handler(jwt)
{
    _auth_endpoints.route("POST", "/api/v1/users/register", false);

    _auth_endpoints.route("GET", "api/v1/*", false);
}

std::shared_ptr<AuthInterceptor::OutgoingResponse> AuthInterceptor::intercept(const std::shared_ptr<IncomingRequest>& request) 
{
    auto r = _auth_endpoints.getRoute(request->getStartingLine().method, request->getStartingLine().path);
    if(r && !r.getEndpoint())
        return nullptr;

    auto authHeader = request->getHeader(oatpp::web::protocol::http::Header::AUTHORIZATION);
    auto authObject = std::static_pointer_cast<JWT::Payload>(_auth_handler.handleAuthorization(authHeader));

    if (authObject) 
    {
        request->putBundleData("user_id", authObject->user_id);
        return nullptr;
    }

    throw oatpp::web::protocol::http::HttpError(oatpp::web::protocol::http::Status::CODE_401, "Unauthorized", {});
}