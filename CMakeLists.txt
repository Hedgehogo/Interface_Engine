cmake_minimum_required(VERSION 3.21)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)
if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions(-O2)
endif ()

file(GLOB_RECURSE src "lib/ui/*.h" "lib/ui/*.hpp" "lib/ui/*.cpp" "lib/modules/appendix/*.hpp" "lib/modules/appendix/*.cpp" "lib/modules/appendix/*.inl")

add_subdirectory(lib/modules/modules/yaml-cpp)

add_library(${PROJECT_NAME} ${src})

set(SFML_PATH_1 "\\usr\\lib\\cmake\\SFML")
set(SFML_PATH_2 "C:\\SFML-2.5.1-clion\\lib\\cmake\\SFML")
set(SFML_PATH_3 "\\home\\andrewkoro105\\SFML-2.5.1\\lib\\cmake\\SFML")

if(EXISTS ${SFML_PATH_2})
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

if(EXISTS ${SFML_PATH_1})
    set(SFML_DIR ${SFML_PATH_1})
elseif(EXISTS ${SFML_PATH_2})
    set(SFML_DIR ${SFML_PATH_2})
else()
    set(SFML_DIR ${SFML_PATH_3})
endif()

set(CMAKE_MODULE_PATH "${cmaKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-system yaml-cpp)

add_executable(${PROJECT_NAME}_ex main.cpp)

target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
