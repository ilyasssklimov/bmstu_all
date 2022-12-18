#include <sstream>
#include <cassert>
#include <iomanip>
#include "jwt/signature/signature.h"
#include "base64/base64.h"
#include "sha256/hmac_sha256.h"


static std::string remove_quotes(std::string str)
{
	std::string upd_str = str;

	if (str[0] == '"')
		upd_str.erase(0, 1);
	if (str[str.size() - 1] == '"')
		upd_str.erase(upd_str.size() - 1);

	return upd_str;
}


std::string Signature::encode(std::string secret_key)
{
	std::string json_header = _header.get_json_header();
	std::string json_payload = _payload.get_json_payload();
	std::string union_data = base64_encode(json_header, true) + "." + base64_encode(json_payload, true);

	if (remove_quotes(_header.get_algorithm()) == "HS256")
	{
		std::stringstream ss_signature;
		std::vector<uint8_t> out(SHA256_HASH_SIZE); 
		hmac_sha256(secret_key.data(), secret_key.size(), 
			        union_data.data(), union_data.size(), 
			        out.data(), out.size());

		for (uint8_t x : out)
			ss_signature << std::hex << std::setfill('0') << std::setw(2) << (int)x;

		_signature = base64_encode(ss_signature.str(), true);
		_signature = _signature.substr(0, _signature.size() - 2);
		return _signature;
	}

	return {};
}


std::string Signature::get_signature()
{
	return _signature;
}