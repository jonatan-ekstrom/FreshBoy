# List utility header and source files.
set(utilHeaders bits.h)
set(utilSources "")

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${utilSources})

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag headers for installation.
install(FILES ${utilHeaders} DESTINATION include/gb/utils)
