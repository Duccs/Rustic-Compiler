# Create the library
add_library(lib-parser STATIC 
    Parser.cpp 
    Parser.h
    Node.cpp 
    Node.h
)

# Link the library
# Needs to be public... Probably...
target_include_directories(lib-parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Throw in other libraries needed. Avoid double throwing cuz why.
target_link_libraries(lib-parser PUBLIC 
    lib-symbol
    lib-scanner
    lib-debug
    lib-instructions
)