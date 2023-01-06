add_executable(test_data
        src/test_repository/user.cpp
        src/test_repository/post.cpp
        src/test_repository/comment.cpp)

target_include_directories(test_data PUBLIC include)
target_link_libraries(test_data data_access_layer GTest::Main gmock)

add_test(NAME test_data COMMAND test_data)


add_executable(int_test_data
        src/int_test_repository/user.cpp
        src/int_test_repository/post.cpp
        src/int_test_repository/comment.cpp)

target_include_directories(int_test_data PUBLIC include)
target_link_libraries(int_test_data data_access_layer GTest::Main)

add_test(NAME int_test_data COMMAND int_test_data)
