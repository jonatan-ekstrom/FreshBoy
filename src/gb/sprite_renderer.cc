#include "sprite_renderer.h"
#include <stdexcept>
#include <utility>
#include "lcd.h"

namespace {

constexpr auto Size{8};

auto GetLine() {
    return std::vector<gb::Shade>{gb::lcd::DisplayWidth,
                                  gb::Shade::Transparent};
}

bool OverlapX(const gb::Sprite& sprite, const unsigned int displayX) {
    const auto x{static_cast<int>(displayX)};
    const auto low{sprite.X()};
    const auto high{low + Size};
    return (x >= low && x < high);
}

bool OverlapY(const gb::Sprite& sprite, const unsigned int displayY, const bool small) {
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
      enabled{false},
      spriteSize{SpriteSize::Small} {}

void SpriteRenderer::Enable() {
    this->enabled = true;
}

void SpriteRenderer::Disable() {
    this->enabled = false;
}

void SpriteRenderer::LargeSprites() {
    this->spriteSize = SpriteSize::Large;
}

void SpriteRenderer::SmallSprites() {
    this->spriteSize = SpriteSize::Small;
}

std::vector<Shade> SpriteRenderer::RenderScanline(const unsigned int line) const {
    if (line >= lcd::DisplayHeight) {
        throw std::runtime_error{"SpriteRenderer - invalid scanline."};
    }

    auto scanline{GetLine()};
    if (!this->enabled) {
        return scanline;
    }

    // Get (up to 10) sprites matching this scanline sorted in priority order.
    const auto sprites{this->table->GetSpritesToRender(line, this->spriteSize)};

    for (auto displayX{0u}; displayX < lcd::DisplayWidth; ++displayX) {
        scanline[displayX] = GetShade(sprites, displayX, line);
    }
    return scanline;
}

Shade SpriteRenderer::GetShade(const std::vector<const Sprite*>& sprites,
                               const unsigned int displayX,
                               const unsigned int displayY) const {
    auto shade{Shade::Transparent};
    for (const auto s : sprites) {
        // If the current pixel does not overlap this sprite, move to the next.
        if (!OverlapX(*s, displayX)) continue;

        const auto dotX{DotX(*s, displayX)};
        const auto dotY{DotY(*s, displayY)};
        const auto& tile{GetTile(*s, dotY)};
        const auto color{tile.Dot(dotX, dotY)};
        const auto zero{s->Palette() == SpritePalette::Zero};
        const auto& palette{zero ? this->obp0 : this->obp1};
        shade = palette->Map(color);

        // If we've found a non-transparent pixel, we're done.
        if (shade != Shade::Transparent) break;
    }
    return shade;
}

unsigned int SpriteRenderer::DotX(const Sprite& sprite,
                                  const unsigned int displayX) {
    if (!OverlapX(sprite, displayX)) {
        throw std::runtime_error{"DisplayX outside sprite."};
    }
    const auto x{static_cast<int>(displayX)};
    auto dotX{x - sprite.X()};
    if (sprite.FlipX()) {
        dotX = Size - 1 - dotX;
    }
    return static_cast<unsigned int>(dotX);
}

unsigned int SpriteRenderer::DotY(const Sprite& sprite,
                                  const unsigned int displayY) const {
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
    return static_cast<unsigned int>(dotY);
}

const Tile& SpriteRenderer::GetTile(const Sprite& sprite,
                                    const unsigned int dotY) const {
    if (this->spriteSize == SpriteSize::Small) {
        return this->banks->GetTileLow(sprite.TileIndex());
    }

    constexpr std::uint8_t mask{0xFE};
    if (dotY < Size) {
        return this->banks->GetTileLow(sprite.TileIndex() & mask);
    }

    return this->banks->GetTileLow((sprite.TileIndex() & mask) + 1);
}

}
