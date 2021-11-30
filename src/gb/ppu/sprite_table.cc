#include "sprite_table.h"
#include <algorithm>
#include <tuple>
#include <stdexcept>
#include "bits.h"
#include "display.h"
#include "log.h"

namespace {

constexpr auto BaseAddress{0xFE00u};
constexpr auto HighAddress{0xFE9Fu};
constexpr auto NumSprites{40u};

constexpr bool ValidAddress(const gb::u16 address) {
    return (address >= BaseAddress && address <= HighAddress);
}

/* Maps a 16-bit address to the corresponding sprite and offset (index). */
constexpr auto GetSpriteAndIndex(const gb::u16 address) {
    constexpr auto SpriteSize{4u};
    const auto adjusted{address - BaseAddress};
    const auto sprite{adjusted / SpriteSize};
    const auto index{adjusted % SpriteSize};
    return std::make_tuple(sprite, index);
}

}

namespace gb {

Sprite::Sprite() : data{} {}

u8 Sprite::Read(const uint index) const {
    return this->data[index];
}

void Sprite::Write(const uint index, const u8 byte) {
    this->data[index] = byte;
}

int Sprite::X() const {
    return this->data[1] - 8;
}

int Sprite::Y() const {
    return this->data[0] - 16;
}

u8 Sprite::TileIndex() const {
    return this->data[2];
}

bool Sprite::FlipX() const {
    return FlagSet(5);
}

bool Sprite::FlipY() const {
    return FlagSet(6);
}

SpritePalette Sprite::Palette() const {
    return FlagSet(4) ? SpritePalette::One : SpritePalette::Zero;
}

bool Sprite::FlagSet(uint bit) const {
    const auto flags{this->data[3]};
    return bit::IsSet(flags, bit);
}

bool Sprite::Hidden() const {
    return FlagSet(7);
}

SpriteTable_::SpriteTable_() : sprites(NumSprites) {}

SpriteTable SpriteTable_::Create() {
    return SpriteTable{new SpriteTable_{}};
}

u8 SpriteTable_::Read(const u16 address) const {
    if (!ValidAddress(address)) {
        log::Warning("SpriteTable - invalid read address: " + log::Hex(address));
        return 0xFF;
    }
    const auto [sprite, index] = GetSpriteAndIndex(address);
    return this->sprites[sprite].Read(index);
}

void SpriteTable_::Write(const u16 address, const u8 byte) {
    if (!ValidAddress(address)) {
        log::Warning("SpriteTable - invalid write address: " + log::Hex(address));
        return;
    }
    const auto [sprite, index] = GetSpriteAndIndex(address);
    this->sprites[sprite].Write(index, byte);
}

SpriteTable_::SpriteRefs
SpriteTable_::GetSpritesToRender(const uint line, const SpriteSize size) const {
    if (line >= lcd::DisplayHeight) {
        throw std::runtime_error{"SpriteTable - invalid scanline."};
    }
    const auto scanline{static_cast<int>(line)};
    const auto spriteHeight{size == SpriteSize::Large ? 16 : 8};

    /*
     * Loop over all sprites starting from the lowest memory address.
     * Find all sprites that has at least one row overlapping the current scanline.
     * Out of these, select the first 10.
     */
    constexpr auto maxCandidates{10u};
    std::vector<const Sprite*> candidates;
    candidates.reserve(maxCandidates);
    for (const auto& sprite : this->sprites) {
        const auto topRow{sprite.Y()};
        const auto bottomRow{topRow + spriteHeight};
        const bool include{scanline >= topRow && scanline < bottomRow};
        if (include) {
            candidates.push_back(&sprite);
        }
        if (candidates.size() == maxCandidates) {
            break;
        }
    }

    /*
     * Sort all sprites in priority (X-coordinate) order, high -> low.
     * Keep previous order if equal (stable sort).
     */
    constexpr auto cmp{[](auto s1, auto s2) { return s1->X() < s2->X(); }};
    std::stable_sort(candidates.begin(), candidates.end(), cmp);

    return candidates;
}

}
