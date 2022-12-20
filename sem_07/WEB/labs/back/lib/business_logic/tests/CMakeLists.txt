add_executable(test_business
        src/builder/user.cpp
        src/builder/post.cpp
        src/builder/comment.cpp
        src/test_repository/user.cpp
        src/test_repository/post.cpp
        src/test_repository/comment.cpp
        src/test_service/guest.cpp
        src/test_service/auth.cpp
        src/test_service/client.cpp
        src/test_service/author.cpp
        src/test_service/admin.cpp)

target_include_directories(test_business PUBLIC include)
target_link_libraries(test_business business_logic GTest::Main)

add_test(NAME test_business COMMAND test_business)
