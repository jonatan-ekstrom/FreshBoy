#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include "background.h"
#include "framebuffer.h"
#include "interrupt.h"
#include "lcd_regs.h"
#include "palettes.h"
#include "sprite_renderer.h"
#include "sprite_table.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "window.h"

namespace gb {

class Lcd_;
using Lcd = std::shared_ptr<Lcd_>;

class Lcd_ {
public:
    using FrameHandler = std::function<void(const Framebuffer::Pixels&)>;
    static Lcd Create(InterruptManager interrupts, const FrameHandler& frameHandler);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    void Tick(unsigned int cycles);
private:
    using Scanline = Framebuffer::Scanline;
    Lcd_(InterruptManager&& interrupts, const FrameHandler& frameHandler);
    bool Accessible(std::uint16_t address) const;
    void FrameReady() const;
    void HandleOam();
    void HandleTransfer();
    void HandleHBlank();
    void HandleVBlank();
    void WriteScanline();
    Scanline GetBgLine();
    Scanline GetWindowLine();
    Scanline GetSpriteLine();
    FrameHandler frameHandler;
    TileBanks banks;
    TileMaps maps;
    SpriteTable table;
    Palettes palettes;
    Background bg;
    Window window;
    SpriteRenderer sprites;
    LcdStat stat;
    LcdControl lcdc;
    Framebuffer frame;
    unsigned int cycleCount;
};

}
