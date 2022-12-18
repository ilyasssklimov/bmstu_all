#include "logger.h"


void log_info(const std::string& message)
{
    #ifdef LOGGING
       std::cout << "INFO: " << message << std::endl;
    #endif
}


void log_error(const std::string& message)
{
    #ifdef LOGGING
        std::cout << "ERROR: " << message << std::endl;
    #endif
}


void log_debug(const std::string& message)
{
    #ifdef LOGGING
        std::cout << "DEBUG: " << message << std::endl;
    #endif
}
