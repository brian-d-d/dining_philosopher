cmake_minimum_required(VERSION 3.15)
project(dining_philosophers)
set(CMAKE_CXX_STANDARD 23)

include_directories(/usr/local/include/)
include_directories(${PROJECT_SOURCE_DIR}/dining)
include_directories(${PROJECT_SOURCE_DIR}/google_testing)

add_subdirectory(dining)
add_subdirectory(google_testing)

add_library(GTestMain SHARED IMPORTED)
add_library(GTest SHARED IMPORTED)
add_library(GMock SHARED IMPORTED)
add_library(GMockMain SHARED IMPORTED)

set_target_properties(GTestMain PROPERTIES IMPORTED_LOCATION /usr/local/lib/libgtest_main.a)
set_target_properties(GTest PROPERTIES IMPORTED_LOCATION /usr/local/lib/libgtest.a)
set_target_properties(GMock PROPERTIES IMPORTED_LOCATION /usr/local/lib/libgmock.a)
set_target_properties(GMockMain PROPERTIES IMPORTED_LOCATION /usr/local/lib/libgmock_main.a)

# Program without any testing
add_executable(main main.cpp)

target_link_libraries(main PUBLIC Philosopher)
target_link_libraries(main PUBLIC Waiter)
target_link_libraries(main PUBLIC Fork)
target_link_libraries(main PUBLIC Monitor)

# Program with google testing
add_executable(gtest gtest.cpp)

target_link_libraries(gtest PUBLIC Dining_GTest)
target_link_libraries(gtest PUBLIC GTestMain)
target_link_libraries(gtest PUBLIC GTest)
target_link_libraries(gtest PUBLIC GMock)
target_link_libraries(gtest PUBLIC GMockMain)