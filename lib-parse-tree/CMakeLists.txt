# Create the library
add_library(lib-parse-tree STATIC 
    Node.cpp 
    Node.h
)

# Link the library
# Needs to be public... Probably...
target_include_directories(lib-parse-tree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Throw in other libraries needed. Avoid double throwing cuz why.
target_link_libraries(lib-parse-tree PUBLIC 
    lib-symbol
    lib-debug
)