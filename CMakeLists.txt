cmake_minimum_required(VERSION 3.11)
project(Interface_Engine CXX)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
set(BUILD_SHARED_LIBS ON)

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
        curl
        GIT_REPOSITORY https://github.com/curl/curl.git
        GIT_TAG curl-8_0_1
        FIND_PACKAGE_ARGS NAMES CURL
)
FetchContent_Declare(
        localisation
        GIT_REPOSITORY https://github.com/Andrewkoro105/Localisation_System.git
        GIT_TAG master
        FIND_PACKAGE_ARGS NAMES localisation
)
FetchContent_Declare(
        Box_Ptr
        GIT_REPOSITORY https://github.com/Andrewkoro105/Box_Ptr.git
        GIT_TAG master
        FIND_PACKAGE_ARGS NAMES Box_Ptr
)

FetchContent_Populate(yaml-cpp)

file(READ "${yaml-cpp_SOURCE_DIR}/CMakeLists.txt" yaml-cpp_CMAKE)

string(REGEX REPLACE
        "cmake_dependent_option\\(YAML_CPP_INSTALL[^\\)]+\\)"
        "set(YAML_CPP_INSTALL ON)"
        yaml-cpp_CMAKE_UPDATED
        "${yaml-cpp_CMAKE}")

file(WRITE "${yaml-cpp_SOURCE_DIR}/CMakeLists.txt" "${yaml-cpp_CMAKE_UPDATED}")

add_subdirectory(${yaml-cpp_SOURCE_DIR})

FetchContent_MakeAvailable(SFML yaml-cpp curl localisation Box_Ptr)

find_package(ImageMagick COMPONENTS Magick++ MagickCore)

message("<=================[ImageMagick]=================>")
message(${ImageMagick_FOUND})

if(DEFINED ImageMagick_INCLUDE_DIRS)
    message(${ImageMagick_INCLUDE_DIRS})
endif()

if(DEFINED ImageMagick_LIBRARIES)
    message(${ImageMagick_LIBRARIES})
endif()

message("<=================[ImageMagick]=================>")

configure_file(lib/config.h.in lib/config.h)

set(libraries
        sfml-graphics sfml-system sfml-window
        yaml-cpp
        libcurl
        localisation
        Box_Ptr
        )

foreach(lib IN LISTS libraries)
    set_target_properties(${lib} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endforeach()
set_target_properties(openLib PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(example-resources/modules)


file(GLOB_RECURSE src "lib/*.cpp")
file(GLOB_RECURSE headers "lib/*.hpp")

add_library(${PROJECT_NAME} ${src} ${headers})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib>
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/lib>
        ${ImageMagick_INCLUDE_DIRS}
)

foreach(lib IN LISTS libraries)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${lib})
endforeach()
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_executable(${PROJECT_NAME}_ex main.cpp)
target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_ex PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


file(GLOB_RECURSE test_src "test/_test/*.cpp")
add_executable(${PROJECT_NAME}_tests ${test_src})
target_link_libraries(${PROJECT_NAME}_tests PUBLIC gtest gtest_main ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_tests PUBLIC test)
set_target_properties(${PROJECT_NAME}_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE test_images "test/_test/*.png" "test/_test/*.txt" "test/_test/*.glsl")
foreach(test_image IN LISTS test_images)
    get_filename_component(test_image_name ${test_image} NAME)
    configure_file(${test_image} ${CMAKE_BINARY_DIR}/bin/test-src/${test_image_name} COPYONLY)
endforeach()

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