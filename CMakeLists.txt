cmake_minimum_required(VERSION 3.15)
project(dining_philosophers)
set(CMAKE_CXX_STANDARD 23)

add_library(Philosopher INTERFACE Philosopher.hpp)
add_library(Waiter INTERFACE waiter.hpp)
add_library(Fork INTERFACE fork.hpp)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC Philosopher)
target_link_libraries(main PUBLIC Waiter)
target_link_libraries(main PUBLIC Fork)

