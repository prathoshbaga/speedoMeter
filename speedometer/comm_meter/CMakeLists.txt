add_library(commMeter STATIC commMeter.cpp)
target_include_directories(commMeter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(pipe PUBLIC pipe)
target_include_directories(commMeter PUBLIC ../../pipe/)