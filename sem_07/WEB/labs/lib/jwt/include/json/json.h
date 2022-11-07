#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iostream>


class JSON
{
public:
	static std::string fields_to_json(std::vector<std::string> fields);
	static std::vector<std::string> json_to_fields(std::string json);
};