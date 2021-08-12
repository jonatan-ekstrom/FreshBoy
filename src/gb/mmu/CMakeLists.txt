# List MMU header and source files.
set(mmuHeaders boot.h memory.h)
set(mmuSources memory.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${mmuSources})

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag headers for installation.
install(FILES ${mmuHeaders} DESTINATION include/gb/mmu)
