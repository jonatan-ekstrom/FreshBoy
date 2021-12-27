#pragma once
#include <functional>
#include <memory>
#include "background.h"
#include "color.h"
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

/* Main class of the PPU component, represents the LCD. */
class Lcd_ {
public:
    /* Callback function for signaling that a frame is ready for rendering. */
    using FrameHandler = std::function<void(const FrameBuffer::Pixels&)>;

    /* Static constructor. */
    static Lcd Create(InterruptManager interrupts, FrameHandler frameHandler);

    /* Read byte from VRAM or I/O register. */
    u8 Read(u16 address) const;

    /* Write byte to VRAM or I/O register. */
    void Write(u16 address, u8 byte);

    /* Step the PPU the provided number of CPU cycles. */
    void Tick(uint cycles);

    /* Switches to the next available color map for rendering. */
    void NextColorMap();
private:
    using Wly = Window::Wly;
    Lcd_(InterruptManager&& interrupts, FrameHandler&& frameHandler);
    bool Enabled() const;
    bool Accessible(u16 address) const;
    void Enable();
    void Disable();
    void FrameReady();
    void HandleOam();
    void HandleTransfer();
    void HandleHBlank();
    void HandleVBlank();
    void RenderScanline();
    void RenderDisabled(Dot* line) const;
    void RenderBg(uint ly, Dot* line);
    void RenderWindow(uint ly, Dot* line);
    void RenderSprites(uint ly, Dot* line);
    FrameHandler frameHandler;
    TileBanks tileBanks;
    TileMaps tileMaps;
    SpriteTable table;
    Palettes palettes;
    Background bg;
    Window window;
    SpriteRenderer sprites;
    LcdStat stat;
    LcdControl lcdc;
    ColorMaps colorMaps;
    FrameBuffer frame;
    Wly wly;
    uint cycleCount;
    bool firstFrame;
};

}
