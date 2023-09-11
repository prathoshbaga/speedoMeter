cmake_minimum_required(VERSION 3.16.3)

project(SpeedGenerator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread")

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(comm_generator)
add_subdirectory(value_generator)

target_link_libraries(${PROJECT_NAME} PRIVATE pipe)
target_link_libraries(${PROJECT_NAME} PRIVATE value_generator)
target_link_libraries(${PROJECT_NAME} PRIVATE commGenerator)