# List application sources.
set(appSources demo.cc main.cc)

# Add main executable target.
add_executable(app ${appSources})

# Add dependency on the 'gb' library.
target_link_libraries(app PRIVATE gb)

# Add dependency on the 'media' library
target_link_libraries(app PRIVATE media)

# Tag app for installation.
install(TARGETS app DESTINATION bin)

# Output binary to build directory.
set_target_properties(app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
                      OUTPUT_NAME gameboy)
