#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "jwt/header/header.h"
#include "jwt/payload/payload.h"

#define SHA256_HASH_SIZE 32


class Signature
{
public:
	explicit Signature(const Header& header, const Payload& payload): _header(header), _payload(payload) {}
	explicit Signature(const std::string& signature): _signature(signature) {}
	explicit Signature() = default;

	std::string encode(std::string secret_key);
	std::string get_signature();

private:
	Header _header;
	Payload _payload;
	std::string _signature;
};