cmake_minimum_required(VERSION 3.14)
project(rw-json)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
    nlohmann_json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
    DOWNLOAD_NO_EXTRACT TRUE
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/include/nlohmann
)

FetchContent_MakeAvailable(nlohmann_json)

add_executable(rw-json main.cpp)

target_include_directories(rw-json PRIVATE ${CMAKE_BINARY_DIR}/include)