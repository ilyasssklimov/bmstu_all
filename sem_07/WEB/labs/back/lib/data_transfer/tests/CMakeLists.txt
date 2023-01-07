add_executable(e2e_test
        src/e2e_test/author_actions.cpp)

target_include_directories(e2e_test PUBLIC include)
target_link_libraries(e2e_test 
        business_logic 
        data_access_layer
        data_transfer
        utils
        GTest::Main)

add_test(NAME e2e_test COMMAND e2e_test)
