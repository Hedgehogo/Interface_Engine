cmake_minimum_required(VERSION 3.21)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)
#[[
add_definitions(-O2)
]]

file(GLOB_RECURSE src "lib/ui/*.cpp" "lib/ui/*.h" "lib/ui/*.hpp" "lib/yaml/yamlWithSfml/*.hpp" "lib/yaml/yamlWithSfml/*.cpp")

add_subdirectory(lib/yaml/yaml-cpp)

add_library(${PROJECT_NAME} ${src})

set(SFML_PATH_1 "E:\\SFML-2.5.1\\lib\\cmake\\SFML")
set(SFML_PATH_2 "C:\\SFML-2.5.1-clion\\lib\\cmake\\SFML")
set(SFML_PATH_3 "\\home\\andrewkoro105\\SFML-2.5.1\\lib\\cmake\\SFML")

if(EXISTS ${SFML_PATH_1} OR EXISTS ${SFML_PATH_2})
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

#[[set_target_properties(Interface_Engine PROPERTIES PUBLIC_HEADER "UI.h")

export(TARGETS Interface_Engine FILE Interface_Engine-config.cmake)

install(TARGETS Interface_Engine ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/public_headers")]]

add_executable(${PROJECT_NAME}_ex main.cpp)

#find_library(`Yes_Science` Interface_Engine)
target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
