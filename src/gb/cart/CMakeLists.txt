# List cartridge source files.
set(cartSources cartridge.cc file.cc header.cc mbc.cc mbc1.cc mbc3.cc rom.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${cartSources})

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
