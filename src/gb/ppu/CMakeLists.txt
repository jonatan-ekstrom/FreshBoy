# List PPU source files.
set(ppuSources
    background.cc
    bg_base.cc
    dot.cc
    framebuffer.cc
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
target_include_directories(gb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
