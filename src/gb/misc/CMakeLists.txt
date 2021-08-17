# List misc source files.
set(miscSources input.cc serial.cc timer.cc)

# Add misc sources to 'gb' target.
target_sources(gb PRIVATE ${miscSources})

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
