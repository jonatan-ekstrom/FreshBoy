# List CPU header and source files.
set(cpuHeaders cpu.h interrupt.h)
set(cpuSources cpu.cc interrupt.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${cpuSources})

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag headers for installation.
install(FILES ${cpuHeaders} DESTINATION include/gb/cpu)
