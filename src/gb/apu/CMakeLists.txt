# List APU source files.
set(apuSources apu.cc channel_3.cc channel_4.cc components.cc tone.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${apuSources})

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

