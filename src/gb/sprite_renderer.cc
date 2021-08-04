#include "sprite_renderer.h"
#include <stdexcept>
#include <utility>
#include "lcd.h"

namespace {

auto GetLine() {
    return std::vector<gb::Shade>{gb::lcd::DisplayWidth,
                                  gb::Shade::Transparent};
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
    const auto x{static_cast<int>(displayX)};
    const auto y{static_cast<int>(displayY)};

    auto shade{Shade::Transparent};
    for (const auto s : sprites) {
        // If the current pixel does not overlap this sprite, move to the next.
        if (x < s->X() || x > (s->X() + 7)) continue;

        const auto& palette{s->Palette() == SpritePalette::Zero ?
                            this->obp0 :
                            this->obp1};
        // 0 <= (x - s->X()) <= 7
        // 0 <= (y - s->Y()) <= 15
        auto dotX{static_cast<unsigned int>(x - s->X())};
        auto dotY{static_cast<unsigned int>(y - s->Y())};

        if (s->FlipX()) {
            dotX = 7 - dotX;
        }

        if (this->spriteSize == SpriteSize::Small) {
            if (s->FlipY()) {
                dotY = 7 - dotY;
            }
            const auto tile{this->banks->GetTileLow(s->TileIndex())};
            shade = palette->Map(tile.Dot(dotX, dotY));
        } else {
            const auto base{static_cast<std::uint8_t>(s->TileIndex() & 0xFE)};
            const auto next{static_cast<std::uint8_t>(base + 1)};
            if (s->FlipY()) {
                dotY = 15 - dotY;
            }
            if (dotY < 8) {
                const auto tile{this->banks->GetTileLow(base)};
                shade = palette->Map(tile.Dot(dotX, dotY));
            } else {
                const auto tile{this->banks->GetTileLow(next)};
                shade = palette->Map(tile.Dot(dotX, dotY - 8));
            }
        }
        // If we've found a non-transparent dot, we're done.
        if (shade != Shade::Transparent) break;
    }
    return shade;
}

}
