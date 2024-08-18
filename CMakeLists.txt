cmake_minimum_required(VERSION 3.10)
project(Xallve)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OPENSSL_USE_STATIC_LIBS TRUE)
set(SOURCE_FILES src/main.cpp src/block.cpp)
find_package(OpenSSL REQUIRED)

include_directories(include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
