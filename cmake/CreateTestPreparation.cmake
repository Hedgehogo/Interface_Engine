function(crete_test_preparation test_lib lib_test lib_dir test_dir test_lib_dir src_test_dir)
	file(GLOB_RECURSE src "test-preparation/*.cpp")
	file(GLOB_RECURSE headers "test-preparation/*.hpp" "test-preparation/*.inl")

	add_executable(Test_Preparation ${src} ${headers})
	target_link_libraries(Test_Preparation PUBLIC absl::flat_hash_map ctre)
	target_include_directories(Test_Preparation PUBLIC ${CMAKE_BINARY_DIR}/test-preparation/)
	set_target_properties(Test_Preparation PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

	configure_file("test-preparation/config.hpp.in" "test-preparation/config.hpp")
	get_target_property(executable Test_Preparation OUTPUT_NAME)

	add_dependencies(${test_lib} Test_Preparation)
	add_dependencies(${lib_test} Test_Preparation)

	set(executable "")
	if(WIN32)
		set(executable "${CMAKE_BINARY_DIR}/bin/Test_Preparation.exe")
	else()
		set(executable "${CMAKE_BINARY_DIR}/bin/Test_Preparation")
	endif()
	
	add_custom_command(TARGET Test_Preparation POST_BUILD COMMAND ${executable})
endfunction()