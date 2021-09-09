#include "lcd.h"
#include <stdexcept>
#include <utility>
#include "display.h"
#include "log.h"

namespace gb {

Lcd Lcd_::Create(InterruptManager interrupts, const FrameHandler& frameHandler) {
    return Lcd{new Lcd_{std::move(interrupts), frameHandler}};
}

Lcd_::Lcd_(InterruptManager&& interrupts, const FrameHandler& frameHandler)
    : frameHandler{frameHandler},
      banks{TileBanks_::Create()},
      maps{TileMaps_::Create()},
      table{SpriteTable_::Create()},
      palettes{},
      bg{this->banks,
         this->maps,
         this->palettes.Background()},
      window{this->banks,
             this->maps,
             this->palettes.Background()},
      sprites{this->banks,
              this->table,
              this->palettes.Object0(),
              this->palettes.Object1()},
      stat{std::move(interrupts)},
      lcdc{},
      frame{},
      cycleCount{0},
      firstFrame{false} {}

u8 Lcd_::Read(const u16 address) const {
    if (!Accessible(address)) {
        return 0xFF;
    }

    // Tile banks
    if (address >= 0x8000 && address <= 0x97FF) {
        return this->banks->Read(address);
    }

    // Tile maps
    if (address >= 0x9800 && address <= 0x9FFF) {
        return this->maps->Read(address);
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
        this->banks->Write(address, byte);
        return;
    }

    // Tile maps
    if (address >= 0x9800 && address <= 0x9FFF) {
        this->maps->Write(address, byte);
        return;
    }

    // OAM
    if (address >= 0xFE00 && address <= 0xFE9F) {
        this->table->Write(address, byte);
        return;
    }

    // LCDC
    if (address == 0xFF40) {
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
        constexpr auto cyclesPerFrame{70224};
        if (this->cycleCount < cyclesPerFrame) return;
        this->cycleCount %= cyclesPerFrame;
        FrameReady();
        return;
    }

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
            throw std::runtime_error{"Unknown state in PPU state machine."};
    }
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

    // Palettes
    if (address >= 0xFF47 && address <= 0xFF49) {
        return mode != LcdMode::Transfer;
    }

    return true;
}

void Lcd_::Enable() {
    this->cycleCount = 0;
    this->firstFrame = true;
}

void Lcd_::Disable() {
    this->cycleCount = 0;
    this->frame.Reset();
    this->stat.Reset();
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
        if (this->lcdc.WindowEnabled()) {
            RenderWindow(ly, line);
        }
    } else {
        RenderDisabled(line);
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
    this->window.RenderScanline(ly, line);
}

void Lcd_::RenderSprites(uint ly, Dot *const line) {
    this->sprites.SetSize(this->lcdc.ObjectSize());
    this->sprites.RenderScanline(ly, line);
}

}
