#include "sprite_renderer.h"
#include <stdexcept>
#include <utility>
#include "display.h"

namespace {

constexpr auto Size{8};

auto GetLine() {
    return std::vector<gb::Dot>{gb::lcd::DisplayWidth,
                                gb::Dot{gb::Shade::Transparent,
                                        gb::Layer::Object}};
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
      spriteSize{SpriteSize::Small} {}


void SpriteRenderer::SetSize(const SpriteSize size) {
    this->spriteSize = size;
}

std::vector<Dot> SpriteRenderer::RenderScanline(const unsigned int line) const {
    if (line >= lcd::DisplayHeight) {
        throw std::runtime_error{"SpriteRenderer - invalid scanline."};
    }

    auto scanline{GetLine()};

    // Get (up to 10) sprites matching this scanline sorted in priority order.
    const auto sprites{this->table->GetSpritesToRender(line, this->spriteSize)};

    for (auto displayX{0u}; displayX < lcd::DisplayWidth; ++displayX) {
        scanline[displayX] = GetDot(sprites, displayX, line);
    }
    return scanline;
}

Dot SpriteRenderer::GetDot(const std::vector<const Sprite*>& sprites,
                           unsigned int displayX,
                           unsigned int displayY) const {
    Dot dot{Shade::Transparent, Layer::Object};
    for (const auto s : sprites) {
        // If the current pixel does not overlap this sprite, move to the next.
        if (!OverlapX(*s, displayX)) continue;

        const auto dotX{DotX(*s, displayX)};
        const auto dotY{DotY(*s, displayY)};
        const auto& tile{GetTile(*s, dotY)};
        const auto color{tile.Color(dotX, dotY)};
        const auto zero{s->Palette() == SpritePalette::Zero};
        const auto& palette{zero ? this->obp0 : this->obp1};
        const auto shade = palette->Map(color);

        // If we've found a non-transparent pixel, we're done.
        if (shade != Shade::Transparent) {
            dot.Tone = shade;
            dot.Level = s->Hidden() ? Layer::Hidden : Layer::Object;
            break;
        }
    }
    return dot;
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

    constexpr auto mask{0xFE};
    if (dotY < Size) {
        return this->banks->GetTileLow(sprite.TileIndex() & mask);
    }

    return this->banks->GetTileLow((sprite.TileIndex() & mask) + 1);
}

}
