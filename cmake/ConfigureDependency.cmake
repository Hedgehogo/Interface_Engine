function(get_lib target)
    get_target_property(libs ${target} LINK_LIBRARIES)
    foreach (lib IN LISTS ${libs})
        get_lib(${lib})
        list(libs APPEND libs_${target})
    endforeach ()
    set(libs_${target} ${libs} PARENT_SCOPE)
endfunction()

function(configure_dependency target)
    set(libs
            sfml-graphics sfml-system sfml-window
            yaml-cpp
            libcurl
            localisation-cpp
            box-ptr
            open-lib
            IEML_CBOR_cpp
            RTTB_cpp
    )

    foreach(lib IN LISTS libs)
        set_target_properties(${lib} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    endforeach()

    target_link_libraries(${target} PUBLIC ${libs})

    target_include_directories(${target} PUBLIC ${ImageMagick_INCLUDE_DIRS})

    get_lib(${target})
    
endfunction()