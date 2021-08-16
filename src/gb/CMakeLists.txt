# List gb top level header and source files.
set(gbHeaders gb.h)
set(gbSources gb.cc)

# Add the 'gb' static library.
add_library(gb STATIC ${gbSources})

# Recurse into subdirectories.
add_subdirectory(apu)
add_subdirectory(cpu)
add_subdirectory(cart)
add_subdirectory(misc)
add_subdirectory(mmu)
add_subdirectory(ppu)
add_subdirectory(utils)

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag library for installation.
install(TARGETS gb DESTINATION lib)
install(FILES ${gbHeaders} DESTINATION include/gb)
