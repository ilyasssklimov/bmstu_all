find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)
find_package(jwt-cpp REQUIRED PATHS /mnt/d/cpp-jwt/build)

add_library(data_transfer STATIC
        src/user_interface/entry_point.cpp
        src/user_interface/tech/technological_ui.cpp
        src/user_interface/web/web_ui.cpp
        src/user_interface/web/auth/handler.cpp
        src/user_interface/web/auth/jwt.cpp
        src/user_interface/web/auth/interceptor.cpp
        src/console/guest.cpp
        src/console/client.cpp
        src/console/author.cpp
        src/console/admin.cpp
        src/model_dto/user.cpp
        src/model_dto/post.cpp
        src/model_dto/comment.cpp
        src/controller/guest.cpp)

target_include_directories(data_transfer PUBLIC include)
add_definitions(-DOATPP_SWAGGER_RES_PATH="/mnt/d/it/c++/web/static/api/")

target_link_libraries(data_transfer PUBLIC
        data_access_layer 
        utils
        oatpp::oatpp
        oatpp::oatpp-swagger
        jwt-cpp::jwt-cpp
)
