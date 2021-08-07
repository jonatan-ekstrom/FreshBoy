#include "lcd.h"

namespace {

constexpr bool BitSet(const std::uint8_t byte, const unsigned int bit) {
    return (byte & (1 << bit)) != 0;
}

}

namespace gb {

LcdControl::LcdControl() : lcdc{0x91} {}

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

}
