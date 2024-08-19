cmake_minimum_required(VERSION 3.10)
project(Xallve)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OPENSSL_USE_STATIC_LIBS TRUE)
set(SOURCE_FILES src/block.cpp src/main.cpp)
find_package(OpenSSL REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")
