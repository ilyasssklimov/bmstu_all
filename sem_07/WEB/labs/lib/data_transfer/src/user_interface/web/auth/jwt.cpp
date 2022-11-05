#include "user_interface/web/auth/jwt.hpp"


JWT::JWT(const oatpp::String& secret, const oatpp::String& issuer):
    _secret(secret),
    _issuer(issuer),
    _verifier(jwt::verify().allow_algorithm(jwt::algorithm::hs256{ secret }).with_issuer(issuer)) 
{std::cout << "IINNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n";}


oatpp::String JWT::createToken(const std::shared_ptr<Payload>& payload) 
{
    std::cout << "IN creation\n" << *_issuer << " | " << *_secret << std::endl;

    auto token = jwt::create().set_issuer(_issuer).set_type("JWS")
                              .set_payload_claim("user_id", jwt::claim(payload->user_id))
                              .sign(jwt::algorithm::hs256{ _secret });
    std::cout << "SO NICE\n";
    return token;
}


std::shared_ptr<JWT::Payload> JWT::readAndVerifyToken(const oatpp::String& token) 
{
    auto decoded = jwt::decode(token);
    _verifier.verify(decoded);

    auto payload = std::make_shared<Payload>();
    payload->user_id = decoded.get_payload_claim("user_id").as_string();

    return payload;

}