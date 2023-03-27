cmake_minimum_required(VERSION 3.21)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

include_directories(lib)

file(GLOB_RECURSE src "lib/*.cpp")
file(GLOB_RECURSE headers "lib/*.hpp")
add_library(${PROJECT_NAME} ${src} ${headers})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${headers}")

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

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
FetchContent_MakeAvailable(SFML yaml-cpp localisation)

find_package(ImageMagick COMPONENTS Magick++ MagickCore REQUIRED)

include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${localisation_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PUBLIC
        sfml-graphics sfml-system
        yaml-cpp
        localisation
        ${ImageMagick_LIBRARIES}
)

add_executable(${PROJECT_NAME}_ex main.cpp)
target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})

file(GLOB_RECURSE srcUnitTest "test/*.cpp")
add_executable(unit_tests ${srcUnitTest})
target_link_libraries(unit_tests PUBLIC gtest gtest_main ${PROJECT_NAME})

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