add_executable(test_data
        src/test_user_repository.cpp
        src/test_post_repository.cpp
        src/test_comment_repository.cpp)

target_link_libraries(test_data data_access_layer GTest::Main)

add_test(NAME test_data COMMAND test_data)
