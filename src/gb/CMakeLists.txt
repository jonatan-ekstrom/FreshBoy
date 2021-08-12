# List gb top level header and source files.
set(gbHeaders demo.h)
set(gbSources demo.cc)

# Add the 'gb' static library.
add_library(gb STATIC ${gbSources})

# Recurse into subdirectories.
add_subdirectory(cart)
add_subdirectory(mmu)
add_subdirectory(ppu)

# Reference the 'media' library.
target_link_libraries(gb PUBLIC media)

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag library for installation.
install(TARGETS gb DESTINATION lib)
install(FILES ${gbHeaders} DESTINATION include/gb)
