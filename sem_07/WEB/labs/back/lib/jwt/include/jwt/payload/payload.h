#pragma once

#include <iostream>
#include <string>
#include <vector>


class Payload
{
public:
	explicit Payload() = default;
	explicit Payload(std::vector<std::string> fields): _fields(fields) {}

	void add_field(std::string key, std::string value);
	std::string get_json_payload();
	std::string get_value(std::string key);

private:
    std::vector<std::string> _fields;
};