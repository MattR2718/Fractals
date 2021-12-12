cmake_minimum_required(VERSION 3.10.2)
project(mandelbrot)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(X11 REQUIRED)
find_package(Threads REQUIRED)

include_directories(/usr/include/SFML/)
link_directories(/usr/lib/aarch64-linux-gnu/)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} sfml-graphics sfml-window sfml-system X11)
