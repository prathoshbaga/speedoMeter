cmake_minimum_required(VERSION 3.16.3)


add_library(meter STATIC meterLogic.cpp)
target_include_directories(meter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Qt5Widgets_INCLUDE_DIRS})

# Find Qt
# find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

target_link_libraries(${PROJECT_NAME} PRIVATE commMeter Qt5::Core Qt5::Widgets)
