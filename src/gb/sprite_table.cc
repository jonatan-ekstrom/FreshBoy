#include "sprite_table.h"

namespace gb {

Sprite::Sprite() : data{} {}

std::uint8_t Sprite::Read(const unsigned int index) const {
    return this->data[index];
}

void Sprite::Write(const unsigned int index, const std::uint8_t byte) {
    this->data[index] = byte;
}

int Sprite::X() const {
    return this->data[1] - 8;
}

int Sprite::Y() const {
    return this->data[0] - 16;
}

unsigned int Sprite::TileIndex() const {
    return this->data[2];
}

bool Sprite::FlipX() const {
    return BitSet(5);
}

bool Sprite::FlipY() const {
    return BitSet(6);
}

SpritePalette Sprite::Palette() const {
    return BitSet(4) ? SpritePalette::One : SpritePalette::Zero;
}

bool Sprite::BitSet(const unsigned int bit) const {
    const auto flags{this->data[3]};
    return (flags & (1u << bit)) != 0;
}

bool Sprite::Hidden() const {
    return BitSet(7);
}

}
