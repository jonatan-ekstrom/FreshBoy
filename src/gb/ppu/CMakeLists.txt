# List PPU header and source files.
set(ppuHeaders
    background.h
    bg_base.h
    color.h
    display.h
    lcd.h
    lcd_regs.h
    palettes.h
    sprite_renderer.h
    sprite_table.h
    tile_banks.h
    tile_maps.h
    window.h)

set(ppuSources
    background.cc
    bg_base.cc
    color.cc
    lcd.cc
    lcd_regs.cc
    palettes.cc
    sprite_renderer.cc
    sprite_table.cc
    tile_banks.cc
    tile_maps.cc
    window.cc)

# Add PPU sources to 'gb' target
target_sources(gb PRIVATE ${ppuSources})

# Setup include directories.
target_include_directories(gb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tag headers for installation.
install(FILES ${ppuHeaders} DESTINATION include/gb/ppu)
