# List APU source files.
set(apuSources apu.cc components.cc noise.cc sweep.cc tone.cc wave.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${apuSources})

# Setup include directories.
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

