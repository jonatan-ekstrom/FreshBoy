# Recurse into subdirectories.
add_subdirectory(gb)
add_subdirectory(media)

# Add main executable target.
add_executable(app main.cc)

# Add dependency on the 'gb' library.
target_link_libraries(app PRIVATE gb)

# Tag app for installation.
install(TARGETS app DESTINATION bin)

# Output binary to build directory.
set_target_properties(app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
                      OUTPUT_NAME gameboy)
