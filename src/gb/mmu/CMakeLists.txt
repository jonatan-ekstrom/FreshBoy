# Add MMU sources to 'gb' target.
target_sources(gb PRIVATE memory.cc)

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
