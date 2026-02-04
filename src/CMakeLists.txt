# Create the executable
add_executable(main Main.cpp)

# Link the library
target_link_libraries(main PRIVATE 
    lib-scanner
)