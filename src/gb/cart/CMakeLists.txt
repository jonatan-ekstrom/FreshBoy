# List cartridge header and source files.
set(cartHeaders
    cartridge.h
    file.h
    header.h)

set(cartSources
    cartridge.cc
    file.cc
    header.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${cartSources})

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag headers for installation.
install(FILES ${cartHeaders} DESTINATION include/gb/cart)
