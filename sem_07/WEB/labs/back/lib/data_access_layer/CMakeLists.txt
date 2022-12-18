include(FetchContent)

FetchContent_Declare(
        libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG a6b1d60e74c1427c8ac2324b85cd4a0dc2068332
)
set(PQXX_LIBRARIES pqxx_static)
FetchContent_MakeAvailable(libpqxx)
find_package(PostgreSQL REQUIRED)

add_library(data_access_layer STATIC
        src/model_dal/post.cpp
        src/model_dal/user.cpp
        src/model_dal/comment.cpp
        src/database/pg_database_async.cpp
        src/repository/user.cpp
        src/repository/post.cpp
        src/repository/comment.cpp)

target_link_libraries(data_access_layer business_logic)
target_include_directories(data_access_layer PUBLIC include)
target_link_libraries(data_access_layer utils)

target_link_libraries(data_access_layer "${PQXX_LIBRARIES}")

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
