add_library(commGenerator STATIC commGenerator.cpp)
target_include_directories(commGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(commGenerator PUBLIC pipe)
target_include_directories(commGenerator PUBLIC ../../pipe/)