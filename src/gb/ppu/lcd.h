#pragma once
#include <cstdint>
#include "background.h"
#include "lcd_regs.h"
#include "palettes.h"
#include "sprite_renderer.h"
#include "sprite_table.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "window.h"

namespace gb {

class Lcd {
public:
    Lcd();
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
private:
    void StatInterrupt();
    TileBanks banks;
    TileMaps maps;
    SpriteTable table;
    Palettes palettes;
    Background bg;
    Window window;
    SpriteRenderer sprites;
    LcdControl lcdc;
    LcdStat stat;
};

}
