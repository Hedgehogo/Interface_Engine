function(configure_dependency PROJECT)
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

    target_link_libraries(${PROJECT} PUBLIC ${libs})

    target_include_directories(${PROJECT} PUBLIC ${ImageMagick_INCLUDE_DIRS})
endfunction()