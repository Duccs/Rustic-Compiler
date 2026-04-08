# Create the library
add_library(lib-instructions STATIC 
    Instructions.cpp 
    Instructions.h
)

# Link the library
# Needs to be public... Probably...
target_include_directories(lib-instructions PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Throw in other libraries needed. Avoid double throwing cuz why.
target_link_libraries(lib-instructions PUBLIC 
    # lib-token
)