add_library(jwt STATIC src/sha256/sha256.c
                       src/sha256/hmac_sha256.c
                       src/base64/base64.cpp
                       src/json/json.cpp
                       src/jwt/header/header.cpp
                       src/jwt/payload/payload.cpp
                       src/jwt/signature/signature.cpp
                       src/jwt/jwt.cpp)

target_include_directories(jwt PUBLIC include)

target_link_libraries(jwt PUBLIC utils)
