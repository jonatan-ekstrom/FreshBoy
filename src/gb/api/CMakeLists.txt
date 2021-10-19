# Top level API target for the gameboy emulator.

# Create API header only target.
add_library(api INTERFACE)

# Setup include directories
target_include_directories(api INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Add the api sources to the 'gb' library.
target_sources(gb PRIVATE api.cc)

# Tag the header for installation.
install(FILES api.h DESTINATION include/gb)
