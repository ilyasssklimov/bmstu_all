add_executable(test_data
        src/test_repository/user.cpp
        src/test_repository/post.cpp
        src/test_repository/comment.cpp)

target_include_directories(test_data PUBLIC include)
target_link_libraries(test_data data_access_layer GTest::Main gmock)

add_test(NAME test_data COMMAND test_data)
