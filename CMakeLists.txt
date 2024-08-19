cmake_minimum_required(VERSION 3.10)

project(Xallve)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    src/block.cpp
    src/keypair.cpp
    src/main.cpp
    src/keypairerrors.cpp
)

add_executable(Xallve ${SOURCE_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)
pkg_check_modules(BASE58 REQUIRED libbase58)
find_package(OpenSSL REQUIRED)

target_include_directories(Xallve PRIVATE ${SODIUM_INCLUDE_DIRS} ${BASE58_INCLUDE_DIRS})
target_link_libraries(Xallve PRIVATE ${SODIUM_LIBRARIES} ${BASE58_LIBRARIES} OpenSSL::Crypto)