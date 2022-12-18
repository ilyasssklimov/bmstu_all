add_library(utils STATIC src/logger.cpp
                         src/exception.cpp)

target_include_directories(utils PUBLIC include)
