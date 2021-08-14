#include "lcd_regs.h"
#include <stdexcept>
#include <utility>

namespace {

constexpr bool BitSet(const std::uint8_t byte, const unsigned int bit) {
    return (byte & (1 << bit)) != 0;
}

constexpr void AssignBits(std::uint8_t& to,
                          const std::uint8_t from,
                          const std::uint8_t mask) {
    to = static_cast<std::uint8_t>((to & ~mask) | (from & mask));
}

constexpr void UpdateBit(std::uint8_t& byte, const unsigned int bit, const bool set) {
    const auto mask{1 << bit};
    const auto updated{(byte & ~mask) | (set ? mask : 0)};
    byte = static_cast<std::uint8_t>(updated);
}

constexpr auto StatAddress{0xFF41u};
constexpr auto LyAddress{0xFF44u};
constexpr auto LycAddress{0xFF45u};

}

namespace gb {

LcdControl::LcdControl() : lcdc{0} {}

std::uint8_t LcdControl::Read() const {
    return this->lcdc;
}

void LcdControl::Write(const std::uint8_t byte) {
    this->lcdc = byte;
}

bool LcdControl::LcdEnabled() const {
    return BitSet(this->lcdc, 7);
}

TileMap LcdControl::WindowMap() const {
    return BitSet(this->lcdc, 6) ? TileMap::Low : TileMap::High;
}

bool LcdControl::WindowEnabled() const {
    return BitSet(this->lcdc, 5);
}

TileBank LcdControl::BackgroundBank() const {
    return BitSet(this->lcdc, 4) ? TileBank::High : TileBank::Low;
}

TileMap LcdControl::BackgroundMap() const {
    return BitSet(this->lcdc, 3) ? TileMap::Low : TileMap::High;
}

SpriteSize LcdControl::ObjectSize() const {
    return BitSet(this->lcdc, 2) ? SpriteSize::Large : SpriteSize::Small;
}

bool LcdControl::ObjectsEnabled() const {
    return BitSet(this->lcdc, 1);
}

bool LcdControl::BackgroundEnabled() const {
    return BitSet(this->lcdc, 0);
}

LcdStat::LcdStat(InterruptManager&& interrupts)
    : interrupts{std::move(interrupts)},
      blankLine{false},
      statLine{false},
      stat{0x86}, // 1000 0110
      ly{0},
      lyc{0} {}

LcdMode LcdStat::Mode() const {
    return static_cast<LcdMode>(this->stat & 0x03);
}

std::uint8_t LcdStat::Ly() const {
    return this->ly;
}

std::uint8_t LcdStat::Read(const std::uint16_t address) const {
    if (address == StatAddress) return this->stat;
    if (address == LyAddress) return this->ly;
    if (address == LycAddress) return this->lyc;
    throw std::runtime_error{"LcdStat - invalid read address."};
}

void LcdStat::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (address == StatAddress) {
        AssignBits(this->stat, byte, 0x78); // 0111 1000
        Refresh();
        return;
    }

    if (address == LycAddress) {
        this->lyc = byte;
        Refresh();
        return;
    }

    throw std::runtime_error{"LcdStat - invalid write address"};
}

void LcdStat::SetMode(const LcdMode mode) {
    AssignBits(this->stat, static_cast<std::uint8_t>(mode), 0x03);
    Refresh();
}

void LcdStat::SetLy(const std::uint8_t newLy) {
    if (newLy > 153) {
        throw std::runtime_error{"LcdStat - invalid LY value."};
    }
    this->ly = newLy;
    Refresh();
}

void LcdStat::Refresh() {
    SetLyFlag(this->ly == this->lyc);
    if (UpdateBlankLine()) {
        FireBlank();
    }
    if (UpdateStatLine()) {
        FireStat();
    }
}

void LcdStat::SetLyFlag(const bool flag) {
    UpdateBit(this->stat, 2, flag);
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
    newLine = newLine || (BitSet(this->stat, 6) && (this->ly == this->lyc));
    newLine = newLine || (BitSet(this->stat, 5) && Mode() == LcdMode::Oam);
    newLine = newLine || (BitSet(this->stat, 4) && Mode() == LcdMode::VBlank);
    newLine = newLine || (BitSet(this->stat, 3) && Mode() == LcdMode::HBlank);
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
