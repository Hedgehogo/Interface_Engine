cmake_minimum_required(VERSION 3.21)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    add_definitions(-O2)
endif ()

file(GLOB_RECURSE src "lib/ui/*.h" "lib/ui/*.hpp" "lib/ui/*.cpp" "lib/modules/appendix/*.hpp" "lib/modules/appendix/*.cpp")

add_subdirectory(lib/modules/modules/yaml-cpp)
add_subdirectory(lib/modules/modules/localization_System)

add_library(${PROJECT_NAME} ${src})

set(SFML_PATH_1 "\\usr\\lib\\cmake\\SFML")
set(SFML_PATH_2 "C:\\SFML-2.5.1-clion\\lib\\cmake\\SFML")

if(EXISTS ${SFML_PATH_2})
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

if(EXISTS ${SFML_PATH_1})
    set(SFML_DIR ${SFML_PATH_1})
elseif(EXISTS ${SFML_PATH_2})
    set(SFML_DIR ${SFML_PATH_2})
endif()

set(CMAKE_MODULE_PATH "${cmaKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-system yaml-cpp localisation)

if(WIN32)
    add_executable(${PROJECT_NAME}_ex WIN32 main.cpp)
else()
    add_executable(${PROJECT_NAME}_ex main.cpp)
endif()

target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})

file(GLOB_RECURSE srcUnitTest "test/*.cpp" "test/*.hpp")

add_executable(unit_tests ${srcUnitTest})

target_link_libraries(unit_tests PUBLIC gtest gtest_main ${PROJECT_NAME})
