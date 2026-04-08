# Create the executable
add_executable(Scanner ScannerTest.cpp)

# Link the library
target_link_libraries(Scanner PRIVATE 
    lib-scanner
)

# Copy "code.txt" to the build directory
add_custom_target(copy_code_txt ALL
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/code.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/code.txt"
    COMMENT "Copying code.txt to binary directory..."
)

# Make scanner depend on the copy task
add_dependencies(Scanner copy_code_txt)

# -----------------------------------------------

# Create the executable
add_executable(SymbolTable SymbolTableTest.cpp)

# Link the library
target_link_libraries(SymbolTable PRIVATE 
    lib-symbol
)

# -----------------------------------------------

# Create the executable
add_executable(ParseTree ParseTreeTest.cpp)

# Link the library
target_link_libraries(ParseTree PRIVATE 
    lib-parser
)

# -----------------------------------------------

# Create the executable
add_executable(Parser ParserTest.cpp)

# Link the library
target_link_libraries(Parser PRIVATE 
    lib-parser
)

# -----------------------------------------------

# Create the executable
add_executable(Instructions InstructionsTest.cpp)

# Link the library
target_link_libraries(Instructions PRIVATE 
    lib-instructions
)

# -----------------------------------------------

# Create the executable
add_executable(MachineCode MachineCodeTest.cpp)

# Link the library
target_link_libraries(MachineCode PRIVATE 
    lib-parser
)