# Create a header-only library
add_library(lib-debug INTERFACE)

# Link the library
# INTERFACE means that this library doesn't have its own source files, but it can be linked to other targets, so not PUBLIC...
target_include_directories(lib-debug INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

# Throw in other libraries if needed
target_link_libraries(lib-debug INTERFACE
# Right here like so ↓↓↓
#  ← uncomment     lib-smth
)