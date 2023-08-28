function(configure_dependency PROJECT)
    set(libraries
            sfml-graphics sfml-system sfml-window
            yaml-cpp
            libcurl
            localisation
            Box_Ptr
            openLib
    )

    foreach(lib IN LISTS libraries)
        set_target_properties(${lib} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    endforeach()

    target_link_libraries(${PROJECT} PUBLIC ${lib})

    target_include_directories(${PROJECT} PUBLIC ${ImageMagick_INCLUDE_DIRS})
endfunction()