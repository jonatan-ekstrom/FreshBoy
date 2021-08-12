# List APU header and source files.
set(apuHeaders channel_1.h channel_2.h channel_3.h channel_4.h sound.h)
set(apuSources channel_1.cc channel_2.cc channel_3.cc channel_4.cc sound.cc)

# Add cartridge sources to 'gb' target.
target_sources(gb PRIVATE ${apuSources})

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag headers for installation.
install(FILES ${apuHeaders} DESTINATION include/gb/apu)
