cmake_minimum_required(VERSION 3.11)
include(FetchContent)

include(cmake/ConfigureDependency.cmake)

set(download OFF)

function(dependency_management PROJECT)
	FetchContent_Declare(
			SFML
			GIT_REPOSITORY https://github.com/SFML/SFML.git
			GIT_TAG 2.6.0
			FIND_PACKAGE_ARGS NAMES SFML COMPONENTS graphics network audio window system
	)
	FetchContent_Declare(
			abseil
			GIT_REPOSITORY https://github.com/abseil/abseil-cpp
			GIT_TAG        "20240116.0"
	)
	FetchContent_Declare(
			ctre
			GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions.git
			GIT_TAG        main
			FIND_PACKAGE_ARGS NAMES ctre
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
			IEML_CBOR_cpp
			GIT_REPOSITORY https://github.com/Hedgehogo/IEML-CBOR-cpp.git
			GIT_TAG main
			FIND_PACKAGE_ARGS NAMES IEML_CBOR_cpp
	)
	FetchContent_Declare(
			RTTB_cpp
			GIT_REPOSITORY https://github.com/Hedgehogo/RTTB-cpp.git
			GIT_TAG master
			FIND_PACKAGE_ARGS NAMES RTTB_cpp
	)
	FetchContent_MakeAvailable(SFML abseil ctre curl localisation-cpp box-ptr IEML_CBOR_cpp RTTB_cpp)

	configure_dependency(${PROJECT})
endfunction()