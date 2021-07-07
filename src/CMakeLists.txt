# Parse the media subdirectory
add_subdirectory(media)
add_subdirectory(gb)

# Add main executable target.
add_executable(app main.cc)
target_link_libraries(app PRIVATE gb)
install(TARGETS app DESTINATION bin)
set_target_properties(app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
                      OUTPUT_NAME gameboy)
