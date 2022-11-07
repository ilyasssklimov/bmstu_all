#include "jwt/payload/payload.h"
#include "json/json.h"


void Payload::add_field(std::string key, std::string value)
{
	_fields.push_back(key);
	_fields.push_back(value);
}


std::string Payload::get_json_payload()
{
	return JSON::fields_to_json(_fields);
}


std::string Payload::get_value(std::string key)
{
	for (size_t i = 0; i < _fields.size(); i += 2)
		if (_fields[i] == key)
			return _fields[i + 1];

	return {};
}