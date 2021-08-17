#pragma once
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
#include "types.h"
#include "window.h"

namespace gb {

class Lcd_;
using Lcd = std::shared_ptr<Lcd_>;

class Lcd_ {
public:
    using FrameHandler = std::function<void(const Framebuffer::Pixels&)>;
    static Lcd Create(InterruptManager interrupts, const FrameHandler& frameHandler);
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte);
    void Tick(uint cycles);
private:
    using Scanline = Framebuffer::Scanline;
    Lcd_(InterruptManager&& interrupts, const FrameHandler& frameHandler);
    bool Enabled() const;
    bool Accessible(u16 address) const;
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
    uint cycleCount;
};

}
