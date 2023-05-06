cmake_minimum_required(VERSION 3.11)
project(Interface_Engine CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(BUILD_SHARED_LIBS on)

file(GLOB_RECURSE src "lib/*.cpp")
file(GLOB_RECURSE headers "lib/*.hpp")

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    file(COPY "${CMAKE_CURRENT_LIST_DIR}/lib/" DESTINATION "${CMAKE_CURRENT_LIST_DIR}/include/Interface_Engine/")
    file(GLOB_RECURSE filesToRemove "include/*.cpp")
    file(REMOVE ${filesToRemove})
endif ()

include_directories(lib)

add_library(${PROJECT_NAME} ${src} ${headers})
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
FetchContent_Declare(
        OpenLib
        GIT_REPOSITORY https://github.com/Andrewkoro105/OpenLib.git
        GIT_TAG master
        FIND_PACKAGE_ARGS NAMES openLib
)

FetchContent_MakeAvailable(SFML yaml-cpp localisation OpenLib)

find_package(ImageMagick COMPONENTS Magick++ MagickCore REQUIRED)

include_directories(${typo_SOURCE_DIR}/stc/rttr)
include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${localisation_SOURCE_DIR}/include)
include_directories(${openlib_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC
        sfml-graphics sfml-system
        yaml-cpp
        localisation
        openLib
        ${ImageMagick_LIBRARIES}
)

add_subdirectory(example-resources/modules)

add_executable(${PROJECT_NAME}_ex main.cpp)
target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})

file(GLOB_RECURSE srcUnitTest "test/*.cpp")
add_executable(unit_tests ${srcUnitTest})
target_link_libraries(unit_tests PUBLIC gtest gtest_main ${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX})

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