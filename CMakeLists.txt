cmake_minimum_required(VERSION 3.11)
project(Interface_Engine CXX)
set(CMAKE_CXX_STANDARD 17)

set(BUILD_SHARED_LIBS ON)

include(cmake/AllInclude.cmake)

file(GLOB_RECURSE src "lib/*.cpp")
file(GLOB_RECURSE headers "lib/*.hpp" "lib/*.inl")
set(test_src "")

foreach (path IN LISTS src headers)
	string(REPLACE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/Test_${PROJECT_NAME}" path2 ${path})
	list(APPEND test_src "${path2}")


	if (NOT EXISTS "${path2}")
		file(WRITE "${path2}" "")
	endif ()
endforeach ()

create_IE(
		"${PROJECT_NAME}"
		"${src};${headers}"
		"${CMAKE_CURRENT_SOURCE_DIR}"
		TRUE
)
create_IE(
		"Test_${PROJECT_NAME}"
		"${test_src}"
		"${CMAKE_CURRENT_BINARY_DIR}/Test_${PROJECT_NAME}"
		FALSE
)

add_executable(${PROJECT_NAME}_ex main.cpp)
target_link_libraries(${PROJECT_NAME}_ex PRIVATE ${PROJECT_NAME})
set_target_properties(${PROJECT_NAME}_ex PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(example-resources/modules)

create_tests(${PROJECT_NAME})
create_install_target()

create_projects_checking("${PROJECT_NAME};${PROJECT_NAME}_tests" "${PROJECT_NAME}_tests")
crete_test_preparation(
		"Test_${PROJECT_NAME}"
		"${PROJECT_NAME}_tests"
		"${CMAKE_CURRENT_SOURCE_DIR}/lib/"
		"${CMAKE_CURRENT_SOURCE_DIR}/test/_test/"
		"${CMAKE_CURRENT_BINARY_DIR}/Test_${PROJECT_NAME}/lib/"
		"${CMAKE_CURRENT_BINARY_DIR}/bin/test-src/"
)