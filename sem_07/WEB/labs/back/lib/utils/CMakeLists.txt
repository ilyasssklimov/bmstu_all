add_library(utils STATIC src/logger.cpp
                         src/exception.cpp
                         src/builder/user.cpp
                         src/builder/post.cpp
                         src/builder/comment.cpp)

target_include_directories(utils PUBLIC include)
target_link_libraries(utils business_logic)
