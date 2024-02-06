function(create_install_target)
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
endfunction()