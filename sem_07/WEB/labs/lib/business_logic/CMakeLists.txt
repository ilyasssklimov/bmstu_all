add_library(business_logic STATIC
        src/model_bl/post.cpp
        src/model_bl/user.cpp
        src/model_bl/comment.cpp
        src/service/guest.cpp
        src/service/client.cpp
        src/service/author.cpp
        src/service/admin.cpp)

target_include_directories(business_logic PUBLIC include)
target_link_libraries(business_logic utils)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
