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
    Lcd_(InterruptManager&& interrupts, const FrameHandler& frameHandler);
    bool Enabled() const;
    bool Accessible(u16 address) const;
    void FrameReady();
    void HandleOam();
    void HandleTransfer();
    void HandleHBlank();
    void HandleVBlank();
    void RenderScanline();
    void RenderScreenLine(Dot* line);
    void RenderBgLine(uint ly, Dot* line);
    void RenderWindowLine(uint ly, Dot* line);
    void RenderSpriteLine(uint ly, Dot* line);
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
