#include "sprite_renderer.h"
#include <utility>

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

std::vector<Shade> SpriteRenderer::RenderScanline(unsigned int) const {
    return std::vector<Shade>();
}

}
