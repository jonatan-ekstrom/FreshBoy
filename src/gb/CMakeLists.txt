# Creates the 'gb' static library.
set(gbHeaders
    background.h
    bg_base.h
    cartridge.h
    color.h
    demo.h
    file.h
    header.h
    lcd.h
    palettes.h
    sprite_renderer.h
    sprite_table.h
    tile_banks.h
    tile_maps.h
    window.h)

set(gbSources
    background.cc
    bg_base.cc
    cartridge.cc
    color.cc
    demo.cc
    file.cc
    header.cc
    palettes.cc
    sprite_renderer.cc
    sprite_table.cc
    tile_banks.cc
    tile_maps.cc
    window.cc)

add_library(gb STATIC ${gbSources})
target_include_directories(gb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gb PUBLIC media)
install(TARGETS gb DESTINATION lib)
install(FILES ${gbHeaders} DESTINATION include/gb)
