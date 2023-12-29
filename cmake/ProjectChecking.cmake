function(get_target_include_directories target result proven_dependencies)
    get_target_property(includes ${target} INCLUDE_DIRECTORIES)
    list(APPEND ${result} ${includes})

    get_target_property(interface_includes ${target} INTERFACE_INCLUDE_DIRECTORIES)
    list(APPEND ${result} ${interface_includes})

    get_target_property(dependencies ${target} INTERFACE_LINK_LIBRARIES)

    foreach (dependency IN LISTS dependencies)
        if (TARGET ${dependency} AND NOT ${dependency} IN_LIST proven_dependencies)
            list(APPEND proven_dependencies ${dependency})
            get_target_include_directories(${dependency} dependency_includes "${proven_dependencies}")
            foreach (dependency_include IN LISTS dependency_includes)
                if (NOT ${dependency_include} IN_LIST ${result})
                    list(APPEND ${result} ${dependency_include})
                endif ()
            endforeach ()
        endif ()
    endforeach ()
    set(${result} ${${result}} PARENT_SCOPE)
    set(proven_dependencies ${proven_dependencies} PARENT_SCOPE)
endfunction()

function(projects_checking project_for_sources project_for_include_dirs)
    set(all_sources "")
    set(all_include_dirs "")
    foreach (project IN LISTS project_for_sources)
        get_target_property(sources ${project} SOURCES)
        list(APPEND all_sources ${sources})
    endforeach ()

    foreach (project IN LISTS project_for_include_dirs)
        get_target_include_directories(${project} include_dirs "")
        list(APPEND all_include_dirs ${include_dirs})
    endforeach ()

    configure_file(code-checking/config.hpp.in code-checking/config.hpp)

    add_executable(code_checking code-checking/main.cpp)
    target_include_directories(code_checking PRIVATE ${CMAKE_BINARY_DIR}/code-checking/)

endfunction()