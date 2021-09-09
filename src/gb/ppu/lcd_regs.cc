#include "lcd_regs.h"
#include <stdexcept>
#include <utility>
#include "bits.h"
#include "log.h"

namespace {

constexpr auto StatAddress{0xFF41u};
constexpr auto LyAddress{0xFF44u};
constexpr auto LycAddress{0xFF45u};

}

namespace gb {

LcdControl::LcdControl() : lcdc{0} {}

u8 LcdControl::Read() const {
    return this->lcdc;
}

void LcdControl::Write(const u8 byte) {
    this->lcdc = byte;
}

bool LcdControl::LcdEnabled() const {
    return bit::IsSet(this->lcdc, 7);
}

TileMap LcdControl::WindowMap() const {
    return bit::IsSet(this->lcdc, 6) ? TileMap::High : TileMap::Low;
}

bool LcdControl::WindowEnabled() const {
    return bit::IsSet(this->lcdc, 5);
}

TileBank LcdControl::BackgroundBank() const {
    return bit::IsSet(this->lcdc, 4) ? TileBank::Low : TileBank::High;
}

TileMap LcdControl::BackgroundMap() const {
    return bit::IsSet(this->lcdc, 3) ? TileMap::High : TileMap::Low;
}

SpriteSize LcdControl::ObjectSize() const {
    return bit::IsSet(this->lcdc, 2) ? SpriteSize::Large : SpriteSize::Small;
}

bool LcdControl::ObjectsEnabled() const {
    return bit::IsSet(this->lcdc, 1);
}

bool LcdControl::BackgroundEnabled() const {
    return bit::IsSet(this->lcdc, 0);
}

LcdStat::LcdStat(InterruptManager&& interrupts)
    : interrupts{std::move(interrupts)},
      blankLine{false},
      statLine{false},
      stat{0x06},
      ly{0},
      lyc{0} {}

LcdMode LcdStat::Mode() const {
    return static_cast<LcdMode>(this->stat & 0x03);
}

u8 LcdStat::Ly() const {
    return this->ly;
}

u8 LcdStat::Read(const u16 address) const {
    if (address == StatAddress) return this->stat;
    if (address == LyAddress) return this->ly;
    if (address == LycAddress) return this->lyc;
    log::Warning("LcdStat - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void LcdStat::Write(const u16 address, const u8 byte,
                    const bool allowInterrupts) {
    if (address == StatAddress) {
        const u8 mask{0x78};
        bit::Assign(this->stat, byte, mask);
        Refresh(allowInterrupts);
        return;
    }

    if (address == LycAddress) {
        this->lyc = byte;
        Refresh(allowInterrupts);
        return;
    }

    log::Warning("LcdStat - invalid write address: " + log::Hex(address));
}

void LcdStat::SetMode(const LcdMode mode) {
    const u8 mask{0x03};
    bit::Assign(this->stat, static_cast<u8>(mode), mask);
    Refresh();
}

void LcdStat::SetLy(const u8 newLy) {
    if (newLy > 153) {
        throw std::runtime_error{"LcdStat - invalid LY value."};
    }
    this->ly = newLy;
    Refresh();
}

void LcdStat::Reset() {
    this->ly = 0;
    bit::Clear(this->stat, 0);
    bit::Set(this->stat, 1);
    Refresh(false);
}

void LcdStat::Refresh(const bool allowInterrupts) {
    bit::Update(this->stat, 2, this->ly == this->lyc);

    if (UpdateBlankLine() && allowInterrupts) {
        FireBlank();
    }

    if (UpdateStatLine() && allowInterrupts) {
        FireStat();
    }
}

bool LcdStat::UpdateBlankLine() {
    const auto prevLine{this->blankLine};
    const auto newLine{Mode() == LcdMode::VBlank};
    this->blankLine = newLine;
    return newLine && !prevLine;
}

bool LcdStat::UpdateStatLine() {
    const auto prevLine{this->statLine};

    bool newLine{false};
    newLine = newLine || (bit::IsSet(this->stat, 6) && (this->ly == this->lyc));
    newLine = newLine || (bit::IsSet(this->stat, 5) && Mode() == LcdMode::Oam);
    newLine = newLine || (bit::IsSet(this->stat, 4) && Mode() == LcdMode::VBlank);
    newLine = newLine || (bit::IsSet(this->stat, 3) && Mode() == LcdMode::HBlank);
    this->statLine = newLine;

    return newLine && !prevLine;
}

void LcdStat::FireBlank() const {
    this->interrupts->RequestInterrupt(Interrupt::VBlank);
}

void LcdStat::FireStat() const {
    this->interrupts->RequestInterrupt(Interrupt::Stat);
}

}
