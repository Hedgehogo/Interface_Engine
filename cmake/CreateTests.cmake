function(create_tests PROJECT)
    file(GLOB_RECURSE test_src "test/*.cpp" "test/*.hpp" "test/*.inl")
    add_executable(${PROJECT}_tests ${test_src})
    target_link_libraries(${PROJECT}_tests PUBLIC gtest gtest_main Test_${PROJECT})
    target_include_directories(${PROJECT}_tests PUBLIC test)
    set_target_properties(${PROJECT}_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    file(GLOB_RECURSE test_images "test/*.png" "test/*.txt" "test/*.glsl")
    foreach(test_image IN LISTS test_images)
        get_filename_component(test_image_name ${test_image} NAME)
        configure_file(${test_image} ${CMAKE_BINARY_DIR}/bin/test-src/${test_image_name} COPYONLY)
    endforeach()
endfunction()