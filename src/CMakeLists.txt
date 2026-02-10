# Create the executable
add_executable(main Main.cpp)

# Link the library
target_link_libraries(main PRIVATE 
    lib-scanner
)

# Copy "code.txt" to the build directory
add_custom_target(copy_code_txt ALL
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/code.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/code.txt"
    COMMENT "Copying code.txt to binary directory..."
)

# Make main depend on the copy task
add_dependencies(main copy_code_txt)