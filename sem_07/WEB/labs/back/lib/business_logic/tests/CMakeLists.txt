add_executable(test_business
        src/test_guest_controller.cpp
        src/test_client_controller.cpp
        src/test_author_controller.cpp
        src/test_admin_controller.cpp)

target_include_directories(test_business PUBLIC include)
target_link_libraries(test_business business_logic GTest::Main)

add_test(NAME test_business COMMAND test_business)
