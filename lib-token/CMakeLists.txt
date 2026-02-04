# Create the library
add_library(lib-token STATIC 
    Token.cpp 
    Token.h
    StateMachine.cpp
    StateMachine.h
)

# Link the library
# Needs to be public... Probably...
target_include_directories(lib-token PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Throw in other libraries needed. Avoid double throwing cuz why.
target_link_libraries(lib-token PUBLIC 
)