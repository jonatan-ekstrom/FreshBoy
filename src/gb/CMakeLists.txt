# Add the 'gb' static library.
add_library(gb STATIC gb.cc)

# Recurse into subdirectories.
add_subdirectory(api)
add_subdirectory(apu)
add_subdirectory(cpu)
add_subdirectory(cart)
add_subdirectory(misc)
add_subdirectory(mmu)
add_subdirectory(ppu)
add_subdirectory(utils)

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Tag library for installation.
install(TARGETS gb DESTINATION lib)
