cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(project VERSION 1.0)

find_package(nlohmann_json 3.11.2 REQUIRED)

add_executable(project main.cpp src/writeglTF.cpp src/utils.cpp)
target_include_directories(project PUBLIC include)

target_link_libraries(project PRIVATE nlohmann_json::nlohmann_json)