cmake_minimum_required(VERSION 3.11)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(BUILD_SHARED_LIBS on)

file(GLOB_RECURSE src "lib/*.cpp")
file(GLOB_RECURSE headers "lib/*.hpp")

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.5.1
        FIND_PACKAGE_ARGS NAMES SFML COMPONENTS graphics network audio window system
)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0
        FIND_PACKAGE_ARGS NAMES yaml-cpp
)
FetchContent_Declare(
        localisation
        GIT_REPOSITORY https://github.com/Andrewkoro105/Localisation_System.git
        GIT_TAG master
        FIND_PACKAGE_ARGS NAMES localisation
)
FetchContent_Declare(
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG curl-8_0_1
        FIND_PACKAGE_ARGS NAMES CURL
)

FetchContent_MakeAvailable(SFML yaml-cpp localisation curl)

find_package(ImageMagick COMPONENTS Magick++ MagickCore REQUIRED)

add_library(${PROJECT_NAME} ${src} ${headers})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        ${ImageMagick_INCLUDE_DIRS}
        )
target_link_libraries(${PROJECT_NAME} PUBLIC
        sfml-graphics sfml-system
        yaml-cpp
        localisation
        libcurl
        ${ImageMagick_LIBRARIES}
)

add_subdirectory(example-resources/modules)

add_executable(${PROJECT_NAME}_ex main.cpp)
target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})

# file(GLOB_RECURSE test_src "test/*.cpp")
# add_executable(${PROJECT_NAME}_tests ${test_src})
# target_link_libraries(${PROJECT_NAME}_tests PUBLIC gtest gtest_main ${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/ui DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME} PATTERN "*.hpp")
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/modules DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME} PATTERN "*.hpp")

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
        )

install(EXPORT ${PROJECT_NAME}
        FILE ${PROJECT_NAME}-config.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME}
        )