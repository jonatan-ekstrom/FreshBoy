# List misc header and source files.
set(miscHeaders input.h serial.h timer.h)
set(miscSources input.cc serial.cc timer.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${miscSources})

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag headers for installation.
install(FILES ${miscHeaders} DESTINATION include/gb/misc)
