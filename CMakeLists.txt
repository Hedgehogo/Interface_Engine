cmake_minimum_required(VERSION 3.21)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib)

file(GLOB_RECURSE src "lib/*.cpp")
file(GLOB_RECURSE headers "lib/*.hpp")
add_library(${PROJECT_NAME} ${src} ${headers})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${headers}")

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
find_package(SFML 2.5 REQUIRED graphics network audio window system REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(ImageMagick COMPONENTS Magick++ MagickCore REQUIRED)
include_directories(${ImageMagick_INCLUDE_DIRS})
find_package(localisation REQUIRED)
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