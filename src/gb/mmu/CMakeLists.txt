# List MMU header and source files.
set(mmuHeaders boot.h mmu.h)
set(mmuSources mmu.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${mmuSources})

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag headers for installation.
install(FILES ${mmuHeaders} DESTINATION include/gb/mmu)
