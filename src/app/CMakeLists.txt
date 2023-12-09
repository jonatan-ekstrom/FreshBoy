# List application sources.
set(appSources app.cc main.cc parser.cc)

# Add main executable target.
add_executable(app ${appSources})

# Add dependency on the 'gb' library and its public API.
target_link_libraries(app PRIVATE gb)
target_link_libraries(app PRIVATE api)

# Add dependency on the 'media' library
target_link_libraries(app PRIVATE media)

# Tag app for installation.
install(TARGETS app DESTINATION bin)
install(FILES $<TARGET_RUNTIME_DLLS:app> DESTINATION bin)

# Output binary to build directory.
set_target_properties(app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
                      OUTPUT_NAME FreshBoy)

# Copy dependencies (SDL2.dll on Windows) to output directory.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_custom_command(TARGET app POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_RUNTIME_DLLS:app>
      $<TARGET_FILE_DIR:app>)
endif ()
