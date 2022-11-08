#include "json/json.h"


std::string JSON::fields_to_json(std::vector<std::string> fields)
{
	std::string json = "{";

	for (size_t i = 0; i < fields.size(); i += 2)
		json += "\"" + fields[i] + "\":" + fields[i + 1] + ",";
	
	json.pop_back();
	json += "}";

	return json;
}


std::vector<std::string> JSON::json_to_fields(std::string json)
{
	std::vector<std::string> fields;
	std::string upd_json = json.substr(1, json.size() - 2) + ",";
	
	size_t comma = 0, colon = 0;
	while ((comma = upd_json.find(",")) != std::string::npos && 
		   (colon = upd_json.find(":")) != std::string::npos) 
	{	
		fields.push_back(upd_json.substr(1, colon - 2));
		fields.push_back(upd_json.substr(colon + 1, comma - colon - 1));
	    
	    upd_json.erase(0, comma + 1);
	}

	return fields;
}