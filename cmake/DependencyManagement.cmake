cmake_minimum_required(VERSION 3.11)
include(FetchContent)

include(cmake/ConfigureDependency.cmake)

function(connect_ImageMagick)
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
endfunction()

function(connect_yaml_cpp)
    FetchContent_Declare(
            yaml-cpp
            GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
            GIT_TAG yaml-cpp-0.7.0
            FIND_PACKAGE_ARGS NAMES yaml-cpp
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
endfunction()

function(dependency_management PROJECT)
    FetchContent_Declare(
            SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.0
            FIND_PACKAGE_ARGS NAMES SFML COMPONENTS graphics network audio window system
    )
    FetchContent_Declare(
            curl
            GIT_REPOSITORY https://github.com/curl/curl.git
            GIT_TAG curl-8_0_1
            FIND_PACKAGE_ARGS NAMES CURL
    )
    FetchContent_Declare(
            localisation-cpp
            GIT_REPOSITORY https://github.com/Andrewkoro105/localisation-cpp.git
            GIT_TAG master
            FIND_PACKAGE_ARGS NAMES localisation-cpp
    )
    FetchContent_Declare(
            box-ptr
            GIT_REPOSITORY https://github.com/Andrewkoro105/box-ptr.git
            GIT_TAG master
            FIND_PACKAGE_ARGS NAMES box-ptr
    )
    FetchContent_Declare(
            option_result_cpp
            GIT_REPOSITORY https://github.com/Hedgehogo/option-result-cpp.git
            GIT_TAG main
            FIND_PACKAGE_ARGS NAMES option_result_cpp
    )
    FetchContent_MakeAvailable(SFML curl localisation-cpp box-ptr option_result_cpp)

    connect_yaml_cpp()
    connect_ImageMagick()

    configure_dependency(${PROJECT})
endfunction()