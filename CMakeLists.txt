cmake_minimum_required(VERSION 3.17)
project(PongX)

set(CMAKE_CXX_STANDARD 20)
find_package(SDL2 REQUIRED)

add_executable(PongX main.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})