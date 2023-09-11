# Set the minimum required CMake version
cmake_minimum_required(VERSION 3.16.3)


# Find the Qt5 package
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
    SpeedometerUI.cpp
    # Add other source files
)

set(HEADERS
    SpeedometerUI.hpp
    # Add other header files
)

QT5_WRAP_CPP(MOC_SOURCES ${HEADERS})

add_library(speedoMeterUI ${SOURCES} ${MOC_SOURCES})

set(UI_FILES
    QtDesigner.ui
)

# Use QT5_WRAP_UI to generate C++ code for UI files
QT5_WRAP_UI(UI_HEADERS ${UI_FILES})

# Link your executable with the Qt5 libraries
target_link_libraries(speedoMeterUI Qt5::Core Qt5::Widgets)

# Include Qt directories
target_include_directories(speedoMeterUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Qt5Widgets_INCLUDE_DIRS})

