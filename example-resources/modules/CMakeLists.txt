add_library(Console_Command_Action-${COMMIT_HASH} MODULE ConsoleCommandAction/BasicConsoleCommandAction.cpp)
target_include_directories(Console_Command_Action-${COMMIT_HASH} PUBLIC lib)

set_target_properties(Console_Command_Action-${COMMIT_HASH} PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/example-resources/buildModules
        COMPILE_FLAGS "-fPIC"
)
target_link_libraries(Console_Command_Action-${COMMIT_HASH} PUBLIC Interface_Engine)
