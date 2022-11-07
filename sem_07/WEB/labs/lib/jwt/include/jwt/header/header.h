#pragma once

#include <iostream>
#include <string>


class Header
{
public:
	explicit Header(std::string algorithm, std::string type): _algorithm(algorithm), _type(type) {}
	explicit Header() = default;
	
	std::string get_algorithm();
	std::string get_json_header();

private:
	std::string _algorithm;
	std::string _type;
};
