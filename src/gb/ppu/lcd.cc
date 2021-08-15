#include "lcd.h"
#include <algorithm>
#include <stdexcept>
#include <utility>
#include <vector>

namespace {

void Merge(std::vector<gb::Dot>& dst, const std::vector<gb::Dot>& src) {
    if (dst.size() != src.size()) {
        throw std::runtime_error{"Scanlines must be equal length."};
    }
    std::transform(src.cbegin(), src.cend(),
                   dst.begin(), dst.end(), std::plus<>{});
}

}

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
      cycleCount{0} {}

u8 Lcd_::Read(const std::uint16_t address) const {
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

    throw std::runtime_error{"LCD - Invalid read address."};
}

void Lcd_::Write(const std::uint16_t address, const u8 byte) {
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
        this->lcdc.Write(byte);
        return;
    }

    // STAT
    if (address == 0xFF41) {
        this->stat.Write(address, byte);
        return;
    }

    // SCX & SCY
    if (address >= 0xFF42 && address <= 0xFF43) {
        this->bg.Write(address, byte);
        return;
    }

    // LYC
    if (address == 0xFF45) {
        this->stat.Write(address, byte);
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

    throw std::runtime_error{"LCD - Invalid write address."};
}

void Lcd_::Tick(const uint cycles) {
    this->cycleCount += cycles;
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

bool Lcd_::Accessible(const std::uint16_t address) const {
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

void Lcd_::FrameReady() const {
    this->frameHandler(this->frame.Buffer());
}

void Lcd_::HandleOam() {
    constexpr auto cyclesPerOam{80};
    if (this->cycleCount < cyclesPerOam) return;
    this->cycleCount %= cyclesPerOam;

    // OAM search is done, time to write the scanline.
    WriteScanline();

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

void Lcd_::WriteScanline() {
    const auto ly{this->stat.Ly()};
    auto scanline{Framebuffer::GetScreenLine()};

    if (!this->lcdc.LcdEnabled()) {
        this->frame.WriteLine(scanline, ly);
        return;
    }

    if (this->lcdc.BackgroundEnabled()) {
        Merge(scanline, GetBgLine());
        if (this->lcdc.WindowEnabled()) {
            Merge(scanline, GetWindowLine());
        }
    }

    if (this->lcdc.ObjectsEnabled()) {
        Merge(scanline, GetSpriteLine());
    }

    this->frame.WriteLine(scanline, ly);
}

Lcd_::Scanline Lcd_::GetBgLine() {
    this->bg.UseBank(this->lcdc.BackgroundBank());
    this->bg.UseMap(this->lcdc.BackgroundMap());
    return this->bg.RenderScanline(this->stat.Ly());
}

Lcd_::Scanline Lcd_::GetWindowLine() {
    this->window.UseBank(this->lcdc.BackgroundBank());
    this->window.UseMap(this->lcdc.WindowMap());
    return this->window.RenderScanline(this->stat.Ly());
}

Lcd_::Scanline Lcd_::GetSpriteLine() {
    this->sprites.SetSize(this->lcdc.ObjectSize());
    return this->sprites.RenderScanline(this->stat.Ly());
}

}
