#ifndef LOGGER_H
#define LOGGER_H


#define LOGGING
#include <iostream>


void log_info(const std::string& message);
void log_error(const std::string& message);
void log_debug(const std::string& message);



#endif  // LOGGER_H
