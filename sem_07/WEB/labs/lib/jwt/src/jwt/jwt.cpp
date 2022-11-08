#include "jwt/jwt.h"
#include "base64/base64.h"
#include "json/json.h"
#include "exception.h"



void JWT::set_header(std::string algorithm, std::string type)
{
	_header = Header(algorithm, type);
}
	

void JWT::set_payload(std::vector<std::string> fields)
{
	_payload = Payload(fields);
}


Payload JWT::get_payload()
{
	return _payload;
}


std::string JWT::generate_token(std::string secret_key)
{
	_signature = Signature(_header, _payload);
	std::string header = base64_encode(_header.get_json_header(), true);
	std::string payload = base64_encode(_payload.get_json_payload(), true);
	std::string signature = _signature.encode(secret_key);

	return header + "." + payload + "." + signature;
}


std::string JWT::generate_signature(std::string secret_key)
{
	auto signature = Signature(_header, _payload);
	return signature.encode(secret_key);
}


JWT JWT::get_jwt(std::string token)
{
	std::string upd_token = token;
	size_t dot;

	// header
	if ((dot = upd_token.find(".")) == std::string::npos)
	{
        time_t time_now = time(nullptr);
        throw JWTException(__FILE__, __LINE__, ctime(&time_now));
	}
	std::string json_header = base64_decode(upd_token.substr(0, dot), true);
	std::vector<std::string> header_fields = JSON::json_to_fields(json_header);
	if (header_fields.size() < 4 || header_fields[0] != "alg" || header_fields[2] != "typ")
	{
        time_t time_now = time(nullptr);
        throw JWTException(__FILE__, __LINE__, ctime(&time_now));
	}

	Header header(header_fields[1], header_fields[3]);
	upd_token.erase(0, dot + 1);
	
	// payload
	if ((dot = upd_token.find(".")) == std::string::npos)
	{
        time_t time_now = time(nullptr);
        throw JWTException(__FILE__, __LINE__, ctime(&time_now));
	}
	std::string json_payload = base64_decode(upd_token.substr(0, dot), true);
	std::vector<std::string> payload_fields = JSON::json_to_fields(json_payload);
	
	Payload payload(payload_fields);
	upd_token.erase(0, dot + 1);

	// signature
	Signature signature(upd_token);
	
	// jwt
	JWT jwt(header, payload, signature);

	return jwt;
}

bool JWT::verify(std::string secret_key)
{	 
	return _signature.get_signature() == generate_signature(secret_key);
}