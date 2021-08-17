# List CPU source files.
set(cpuSources cpu.cc interrupt.cc ops.cc switches.cc)

# Add CPU sources to 'gb' target.
target_sources(gb PRIVATE ${cpuSources})

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
