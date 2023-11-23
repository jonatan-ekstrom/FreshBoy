#include "sprite_renderer.h"
#include <stdexcept>
#include <utility>
#include "display.h"

namespace {

constexpr auto Size{8};

/* Returns true if the sprite overlaps the display X-coordinate. */
bool OverlapX(const gb::Sprite& sprite, const gb::uint displayX) {
    const auto x{static_cast<int>(displayX)};
    const auto low{sprite.X()};
    const auto high{low + Size};
    return (x >= low && x < high);
}

/* Returns true if the sprite overlaps the display Y-coordinate. */
bool OverlapY(const gb::Sprite& sprite, const gb::uint displayY, const bool small) {
    const auto y{static_cast<int>(displayY)};
    const auto height{small ? Size : 2 * Size};
    const auto low{sprite.Y()};
    const auto high{low + height};
    return (y >= low && y < high);
}

}

namespace gb {

SpriteRenderer::SpriteRenderer(TileBanks banks, SpriteTable table, Palette obp0, Palette obp1)
    : banks{std::move(banks)},
      table{std::move(table)},
      obp0{std::move(obp0)},
      obp1{std::move(obp1)},
      spriteSize{SpriteSize::Small} {}

void SpriteRenderer::SetSize(const SpriteSize size) {
    this->spriteSize = size;
}

void SpriteRenderer::RenderScanline(const uint ly, Dot *const line) const {
    if (ly >= lcd::DisplayHeight) {
        throw std::runtime_error{"SpriteRenderer - invalid scanline."};
    }

    // Get (up to 10) sprites matching this scanline sorted in priority order.
    const auto sprites{this->table->GetSpritesToRender(ly, this->spriteSize)};
    if (sprites.empty()) return;

    for (auto displayX{0u}; displayX < lcd::DisplayWidth; ++displayX) {
        WriteDot(line[displayX], sprites, displayX, ly);
    }
}

void SpriteRenderer::WriteDot(Dot& dot, const SpriteRefs& sprites,
                              const uint displayX,
                              const uint displayY) const {
    // Loop over all sprites in priority order.
    for (const auto s : sprites) {
        // If the current pixel does not overlap this sprite, move to the next.
        if (!OverlapX(*s, displayX)) continue;

        /*
         * Convert display coordinates to sprite coordinates.
         * Get the corresponding tile and the color index.
         */
        const auto dotX{DotX(*s, displayX)};
        auto dotY{DotY(*s, displayY)};
        const auto& tile{GetTile(*s, dotY)};
        const auto index{tile.Color(dotX, dotY)};

        // If we've found a non-transparent pixel, we're done.
        if (index != ColorIndex::Zero) {
            // Skip the pixel if the sprite is low-priority and the current color index is non-zero.
            const auto current{static_cast<u8>(dot.Index)};
            const auto nonZero{current >= 1 && current <= 3};
            const auto skip{s->Hidden() && nonZero};
            if (skip) break;

            // Get the palette and map the color index to a shade.
            const auto zero{s->Palette() == SpritePalette::Zero};
            const auto& palette{zero ? this->obp0 : this->obp1};
            const auto shade = palette->Map(index);

            // Update the dot's color data.
            dot.Index = index;
            dot.Tone = shade;
            break;
        }
    }
}

uint SpriteRenderer::DotX(const Sprite& sprite,
                          const uint displayX) {
    // Map display X-coordinate to sprite coordinates.
    if (!OverlapX(sprite, displayX)) {
        throw std::runtime_error{"DisplayX outside sprite."};
    }
    const auto x{static_cast<int>(displayX)};
    auto dotX{x - sprite.X()};
    if (sprite.FlipX()) {
        dotX = Size - 1 - dotX;
    }
    return static_cast<uint>(dotX);
}

uint SpriteRenderer::DotY(const Sprite& sprite,
                          const uint displayY) const {
    // Map display Y-coordinate to sprite coordinates.
    const bool small{this->spriteSize == SpriteSize::Small};
    if (!OverlapY(sprite, displayY, small)) {
        throw std::runtime_error{"DisplayY outside sprite."};
    }
    const auto y{static_cast<int>(displayY)};
    const auto height{small ? Size : 2 * Size};
    auto dotY{y - sprite.Y()};
    if (sprite.FlipY()) {
        dotY = height - 1 - dotY;
    }
    return static_cast<uint>(dotY);
}

const Tile& SpriteRenderer::GetTile(const Sprite& sprite,
                                    uint& dotY) const {
    // Small (8x8) sprites occupy only one tile.
    if (this->spriteSize == SpriteSize::Small) {
        return this->banks->GetTileLow(sprite.TileIndex());
    }

    // Large sprites (8x16) occupy two tiles.
    constexpr auto mask{0xFE};
    if (dotY < Size) {
        // Upper tile.
        return this->banks->GetTileLow(sprite.TileIndex() & mask);
    }

    // Lower tile.
    dotY -= Size; // Adjust Y-coordinate.
    return this->banks->GetTileLow((sprite.TileIndex() & mask) + 1);
}

}
