#pragma once


#include <iostream>
#include <string>
#include <vector>

#include "jwt/header/header.h"
#include "jwt/payload/payload.h"
#include "jwt/signature/signature.h"


class JWT
{
public:
	explicit JWT() = default;
	explicit JWT(const Header& header, const Payload& payload, const Signature& signature):
		_header(header), _payload(payload), _signature(signature) {}

	void set_header(std::string algorithm, std::string type);
	void set_payload(std::vector<std::string> fields);
	Payload get_payload();

	std::string generate_token(std::string secret_key);
	std::string generate_signature(std::string secret_key);
	bool verify(std::string secret_key);

	static JWT get_jwt(std::string token);

private:
	Header _header;
	Payload _payload;
	Signature _signature;
};
