cmake_minimum_required(VERSION 3.16.3)
project(Speedometer)

# Find Qt
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Set the source files and UI files
set(SOURCES
    main.cpp
)

# set pthread flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread -fPIC")

# Create the executable
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(comm_meter)
add_subdirectory(meter)
add_subdirectory(meterUI)
target_link_libraries(${PROJECT_NAME} PRIVATE meter)
target_link_libraries(${PROJECT_NAME} PRIVATE commMeter)
target_link_libraries(${PROJECT_NAME} PRIVATE pipe)
target_link_libraries(${PROJECT_NAME} PRIVATE speedoMeterUI)

#set(UI_FILES
#    QtDesigner.ui
#)


# Link against Qt5 modules
#target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
