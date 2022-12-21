find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-swagger  1.3.0 REQUIRED)

add_library(data_transfer STATIC
        src/user_interface/entry_point.cpp
        src/user_interface/tech/technological_ui.cpp
        src/user_interface/web/web_ui.cpp
        src/console/guest.cpp
        src/console/client.cpp
        src/console/author.cpp
        src/console/admin.cpp
        src/model_dto/user.cpp
        src/model_dto/post.cpp
        src/model_dto/comment.cpp
        src/controller/auth.cpp
        src/controller/guest.cpp
        src/controller/client.cpp
        src/controller/author.cpp
        src/controller/admin.cpp)

target_include_directories(data_transfer PUBLIC include)
add_definitions(-DOATPP_SWAGGER_RES_PATH="/mnt/d/it/bmstu_all/sem_07/web/labs/back/static/api/")

target_link_libraries(data_transfer PUBLIC
        data_access_layer 
        utils
        jwt
        oatpp::oatpp
        oatpp::oatpp-swagger
)
