function(create_IE name src src_dir download)
	add_library(${name} SHARED ${src})
	add_library(${name}::${name} ALIAS ${name})
	set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	target_include_directories(${name} PUBLIC
			$<BUILD_INTERFACE:${src_dir}/lib>
			$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/lib>
	)
	set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

	if (download)
		dependency_management(${name})
	else ()
		configure_dependency(${name})
	endif ()
endfunction()