cmake_minimum_required(VERSION 3.21)
project(modules)
set(CMAKE_CXX_STANDARD 17)

add_library(testModule consoleCommandEvent/consoleCommandEvent.cpp)
target_include_directories(testModule PUBLIC lib)
set_target_properties(testModule PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/example-resources/buildModules
        COMPILE_FLAGS ""
)
target_link_libraries(testModule PUBLIC Interface_Engine)