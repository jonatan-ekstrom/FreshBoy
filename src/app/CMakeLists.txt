# List application sources.
set(appSources app.cc main.cc)

# Add main executable target.
add_executable(app ${appSources})

# Add dependency on the 'gb' library and its public API.
target_link_libraries(app PRIVATE gb)
target_link_libraries(app PRIVATE api)

# Add dependency on the 'media' library
target_link_libraries(app PRIVATE media)

# Tag app for installation.
install(TARGETS app DESTINATION bin)

# Output binary to build directory.
set_target_properties(app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
                      OUTPUT_NAME gb++)
