#include "sprite_table.h"
#include <algorithm>
#include <tuple>
#include <stdexcept>

namespace {

constexpr auto BaseAddress{0xFE00u};
constexpr auto HighAddress{0xFE9Fu};
constexpr auto SpriteSize{4u};

bool ValidAddress(const std::uint16_t address) {
    return (address >= BaseAddress && address <= HighAddress);
}

auto GetSpriteAndIndex(const std::uint16_t address) {
    const auto adjusted{address - BaseAddress};
    const auto sprite{adjusted / SpriteSize};
    const auto index{adjusted % SpriteSize};
    return std::make_tuple(sprite, index);
}

}

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

SpriteTable_::SpriteTable_() : sprites(40) {}

SpriteTable SpriteTable_::Create() {
    return SpriteTable{new SpriteTable_()};
}

std::uint8_t SpriteTable_::Read(const std::uint16_t address) const {
    if (!ValidAddress(address)) {
        throw std::runtime_error{"SpriteTable_ - invalid read address."};
    }
    unsigned int sprite, index;
    std::tie(sprite, index) = GetSpriteAndIndex(address);
    return this->sprites[sprite].Read(index);
}

void SpriteTable_::Write(const std::uint16_t address, const std::uint8_t byte) {
    if (!ValidAddress(address)) {
        throw std::runtime_error{"SpriteTable_ - invalid write address."};
    }
    unsigned int sprite, index;
    std::tie(sprite, index) = GetSpriteAndIndex(address);
    this->sprites[sprite].Write(index, byte);
}

std::vector<const Sprite*>
SpriteTable_::GetSpritesToRender(const unsigned int line,
                                 const bool largeSprites) const {
    constexpr auto displayHeight{144};
    if (line >= displayHeight) {
        throw std::runtime_error{"SpriteTable_ - invalid scanline."};
    }
    const auto scanline{static_cast<int>(line)};
    const auto spriteHeight{largeSprites ? 16 : 8};

    constexpr auto maxCandidates{10u};
    std::vector<const Sprite*> candidates;
    candidates.reserve(maxCandidates);
    for (const auto& sprite : this->sprites) {
        const auto topRow{sprite.Y()};
        const auto bottomRow{topRow + spriteHeight - 1};
        const bool include{scanline >= topRow && scanline <= bottomRow};
        if (include) {
            candidates.push_back(&sprite);
        }
        if (candidates.size() == maxCandidates) {
            break;
        }
    }

    // Sort in priority order high -> low.
    const auto cmp{[](auto s1, auto s2) { return s1->X() < s2->X(); }};
    std::stable_sort(candidates.begin(), candidates.end(), cmp);

    return candidates;
}

}
