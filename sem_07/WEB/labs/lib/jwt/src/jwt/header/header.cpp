#include "jwt/header/header.h"
#include "json/json.h"


std::string Header::get_algorithm()
{
	return _algorithm;
}


std::string Header::get_json_header()
{
	return JSON::fields_to_json({
		"alg", _algorithm,
		"typ", _type, 
	});
}
