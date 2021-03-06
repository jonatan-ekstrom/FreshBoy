#include "lcd.h"
#include <stdexcept>
#include <utility>
#include "display.h"
#include "log.h"

namespace gb {

Lcd Lcd_::Create(InterruptManager interrupts, FrameHandler frameHandler) {
    return Lcd{new Lcd_{std::move(interrupts), std::move(frameHandler)}};
}

Lcd_::Lcd_(InterruptManager&& interrupts, FrameHandler&& frameHandler)
    : frameHandler{std::move(frameHandler)},
      tileBanks{TileBanks_::Create()},
      tileMaps{TileMaps_::Create()},
      table{SpriteTable_::Create()},
      palettes{},
      bg{this->tileBanks,
         this->tileMaps,
         this->palettes.Background()},
      window{this->tileBanks,
             this->tileMaps,
             this->palettes.Background()},
      sprites{this->tileBanks,
              this->table,
              this->palettes.Object0(),
              this->palettes.Object1()},
      stat{std::move(interrupts)},
      lcdc{},
      colorMaps{ColorMaps_::Create()},
      frame{this->colorMaps},
      wly{},
      cycleCount{0},
      firstFrame{false} {}

u8 Lcd_::Read(const u16 address) const {
    if (!Accessible(address)) {
        return 0xFF;
    }

    // Tile banks
    if (address >= 0x8000 && address <= 0x97FF) {
        return this->tileBanks->Read(address);
    }

    // Tile maps
    if (address >= 0x9800 && address <= 0x9FFF) {
        return this->tileMaps->Read(address);
    }

    // OAM
    if (address >= 0xFE00 && address <= 0xFE9F) {
        return this->table->Read(address);
    }

    // LCDC
    if (address == 0xFF40) {
        return this->lcdc.Read();
    }

    // STAT
    if (address == 0xFF41) {
        return this->stat.Read(address);
    }

    // SCX & SCY
    if (address >= 0xFF42 && address <= 0xFF43) {
        return this->bg.Read(address);
    }

    // LY & LYC
    if (address >= 0xFF44 && address <= 0xFF45) {
        return this->stat.Read(address);
    }

    // Palettes
    if (address >= 0xFF47 && address <= 0xFF49) {
        return this->palettes.Read(address);
    }

    // WX & WY
    if (address >= 0xFF4A && address <= 0xFF4B) {
        return this->window.Read(address);
    }

    log::Warning("LCD - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Lcd_::Write(const u16 address, const u8 byte) {
    if (!Accessible(address)) {
        return;
    }

    // Tile banks
    if (address >= 0x8000 && address <= 0x97FF) {
        this->tileBanks->Write(address, byte);
        return;
    }

    // Tile maps
    if (address >= 0x9800 && address <= 0x9FFF) {
        this->tileMaps->Write(address, byte);
        return;
    }

    // OAM
    if (address >= 0xFE00 && address <= 0xFE9F) {
        this->table->Write(address, byte);
        return;
    }

    // LCDC
    if (address == 0xFF40) {
        // Handle enabling / disabling of the PPU through LCDC.
        const auto prev{Enabled()};
        this->lcdc.Write(byte);
        const auto curr{Enabled()};
        if (!prev && curr) {
            Enable();
        }
        if (prev && !curr) {
            Disable();
        }
        return;
    }

    // STAT
    if (address == 0xFF41) {
        // Prevent interrupts if LCD is disabled.
        this->stat.Write(address, byte, Enabled());
        return;
    }

    // SCX & SCY
    if (address >= 0xFF42 && address <= 0xFF43) {
        this->bg.Write(address, byte);
        return;
    }

    // LYC
    if (address == 0xFF45) {
        // Prevent interrupts if LCD is disabled.
        this->stat.Write(address, byte, Enabled());
        return;
    }

    // Palettes
    if (address >= 0xFF47 && address <= 0xFF49) {
        this->palettes.Write(address, byte);
        return;
    }

    // WX & WY
    if (address >= 0xFF4A && address <= 0xFF4B) {
        this->window.Write(address, byte);
        return;
    }

    log::Warning("LCD - invalid write address: " + log::Hex(address));
}

void Lcd_::Tick(const uint cycles) {
    this->cycleCount += cycles;

    if (!Enabled()) {
        // If LCD is disabled, just pump empty frames.
        if (this->cycleCount < lcd::CyclesPerFrame) return;
        this->cycleCount %= lcd::CyclesPerFrame;
        FrameReady();
        return;
    }

    // Dispatch to the handler for each mode.
    switch (this->stat.Mode()) {
        case LcdMode::HBlank:
            HandleHBlank();
            return;
        case LcdMode::VBlank:
            HandleVBlank();
            return;
        case LcdMode::Oam:
            HandleOam();
            return;
        case LcdMode::Transfer:
            HandleTransfer();
            return;
        default:
            throw std::runtime_error{"LCD - Unknown mode."};
    }
}

void Lcd_::NextColorMap() {
    this->colorMaps->Next();
}

bool Lcd_::Enabled() const {
    return this->lcdc.LcdEnabled();
}

bool Lcd_::Accessible(const u16 address) const {
    if (!Enabled()) return true;

    const auto mode{this->stat.Mode()};

    // VRAM
    if (address >= 0x8000 && address <= 0x9FFF) {
        return mode != LcdMode::Transfer;
    }

    // OAM
    if (address >= 0xFE00 && address <= 0xFE9F) {
        return mode == LcdMode::HBlank || mode == LcdMode::VBlank;
    }

    return true;
}

void Lcd_::Enable() {
    this->cycleCount = 0;
    this->firstFrame = true;
    this->stat.Enable();
}

void Lcd_::Disable() {
    this->cycleCount = 0;
    this->wly.reset();
    this->frame.Reset();
    this->stat.Disable();
}

void Lcd_::FrameReady() {
    this->frameHandler(this->frame.LockFrame());
    this->firstFrame = false;
}

void Lcd_::HandleOam() {
    constexpr auto cyclesPerOam{80};
    if (this->cycleCount < cyclesPerOam) return;
    this->cycleCount %= cyclesPerOam;

    // OAM search is done, time to render the scanline.
    RenderScanline();

    // Switch to scanline transfer.
    this->stat.SetMode(LcdMode::Transfer);
}

void Lcd_::HandleTransfer() {
    constexpr auto cyclesPerTransfer{172};
    if (this->cycleCount < cyclesPerTransfer) return;
    this->cycleCount %= cyclesPerTransfer;

    // Scanline transfer is done, switch to HBlank.
    this->stat.SetMode(LcdMode::HBlank);
}

void Lcd_::HandleHBlank() {
    constexpr auto cyclesPerHBlank{204};
    if (this->cycleCount < cyclesPerHBlank) return;
    this->cycleCount %= cyclesPerHBlank;

    constexpr auto lastLine{143};
    const auto ly{this->stat.Ly()};
    if (ly == lastLine) {
        // This frame is done, render frame and switch to VBlank.
        FrameReady();
        this->stat.SetMode(LcdMode::VBlank);
    } else {
        // This scanline is done, switch to OAM search.
        this->stat.SetMode(LcdMode::Oam);
    }
    // Start a new scanline.
    this->stat.SetLy(ly + 1);
}

void Lcd_::HandleVBlank() {
    constexpr auto cyclesPerVBlank{456};
    if (this->cycleCount < cyclesPerVBlank) return;
    this->cycleCount %= cyclesPerVBlank;

    constexpr auto numLines{154};
    const auto ly{this->stat.Ly()};
    const auto newLy{static_cast<u8>((ly + 1) % numLines)};
    if (newLy == 0) {
        // VBlank is done, switch to OAM search.
        this->stat.SetMode(LcdMode::Oam);
        this->wly.reset();
    }
    // Start a new scanline.
    this->stat.SetLy(newLy);
}

void Lcd_::RenderScanline() {
    if (this->firstFrame) return;

    const auto ly{this->stat.Ly()};
    const auto line{this->frame.ScanlinePtr(ly)};

    if (this->lcdc.BackgroundEnabled()) {
        RenderBg(ly, line);
    } else {
        RenderDisabled(line);
    }

    if (this->lcdc.WindowEnabled()) {
        RenderWindow(ly, line);
    }

    if (this->lcdc.ObjectsEnabled()) {
        RenderSprites(ly, line);
    }
}

void Lcd_::RenderDisabled(Dot *const line) const {
    this->bg.RenderDisabled(line);
}

void Lcd_::RenderBg(uint ly, Dot *const line) {
    this->bg.UseBank(this->lcdc.BackgroundBank());
    this->bg.UseMap(this->lcdc.BackgroundMap());
    this->bg.RenderScanline(ly, line);
}

void Lcd_::RenderWindow(uint ly, Dot *const line) {
    this->window.UseBank(this->lcdc.BackgroundBank());
    this->window.UseMap(this->lcdc.WindowMap());
    this->window.RenderScanline(ly, this->wly, line);
}

void Lcd_::RenderSprites(uint ly, Dot *const line) {
    this->sprites.SetSize(this->lcdc.ObjectSize());
    this->sprites.RenderScanline(ly, line);
}

}
