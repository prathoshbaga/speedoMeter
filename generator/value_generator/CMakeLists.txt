add_library(value_generator STATIC periodicGenerator.cpp)
target_include_directories(value_generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(SpeedGenerator PRIVATE commGenerator)