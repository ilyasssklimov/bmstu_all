#include "exception.h"


BaseException::BaseException(const std::string &filename, const int line, const char *time, const std::string &message)
{
    error = "Error! " + message + "\n" + time + "Filename: " + filename + ", line # " + std::to_string(line) + ". ";
}

const char* BaseException::what() const noexcept
{
    return error.c_str();
}
