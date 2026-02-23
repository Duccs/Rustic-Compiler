# Create the library
add_library(lib-symbol STATIC 
    Symbol.cpp 
    Symbol.h
)

# Link the library
# Needs to be public... Probably...
target_include_directories(lib-symbol PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Throw in other libraries needed. Avoid double throwing cuz why.
target_link_libraries(lib-symbol PUBLIC 
    lib-debug
)