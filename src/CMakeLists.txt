# Add main executable target.
add_executable(app main.cc)
install(TARGETS app DESTINATION bin)
set_target_properties(app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
                      OUTPUT_NAME gameboy)

