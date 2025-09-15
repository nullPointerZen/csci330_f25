cmake_minimum_required(VERSION 3.10)
project(Chapter01)

set(CMAKE_CXX_STANDARD 17)

add_executable(chapter01 main.cpp)

enable_testing()
add_test(NAME RunExecutable COMMAND chapter01)
