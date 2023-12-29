cmake_minimum_required(VERSION 3.11)
project(Interface_Engine CXX)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

include(cmake/AllInclude.cmake)

file(GLOB_RECURSE src "lib/*.cpp")
file(GLOB_RECURSE headers "lib/*.hpp" "lib/*.inl")

add_library(${PROJECT_NAME} ${src} ${headers})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/lib>
)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

dependency_management(${PROJECT_NAME})

add_executable(${PROJECT_NAME}_ex main.cpp)
target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_ex PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(example-resources/modules)

create_tests(${PROJECT_NAME})
create_install_target()

projects_checking("${PROJECT_NAME};${PROJECT_NAME}_tests" "${PROJECT_NAME}_tests")