#pragma once
#include <array>
#include <memory>
#include <vector>
#include "palettes.h"
#include "types.h"

namespace gb {

/*
 * Enumeration of the available sprite sizes.
 * Small: 8x8
 * Large: 8x16
 */
enum class SpriteSize {
    Small,
    Large
};

/* Represents a sprite, i.e. an 'object' stored in OAM. */
class Sprite {
public:
    /* Constructs a new instance of a sprite. */
    Sprite();

    /* Read a byte of data from the sprite. */
    u8 Read(uint index) const;

    /* Write a byte of data to the sprite. */
    void Write(uint index, u8 byte);

    /* The X-coordinate of the top-left corner. */
    int X() const;

    /* The Y-coordinate of the top-left corner. */
    int Y() const;

    /* The index of the tile the sprite uses. */
    u8 TileIndex() const;

    /* True if the sprite is horizontally mirrored. */
    bool FlipX() const;

    /* True if the sprite is vertically mirrored. */
    bool FlipY() const;

    /* Returns which palette the sprite uses. */
    SpritePalette Palette() const;

    /* True if the sprite is 'hidden', i.e. behind the background. */
    bool Hidden() const;
private:
    bool FlagSet(uint bit) const;
    std::array<u8, 4> data;
};

class SpriteTable_;
using SpriteTable = std::shared_ptr<SpriteTable_>;

/* Represents the sprite table, i.e. object attribute memory (OAM). */
class SpriteTable_ {
public:
    /* A list of (non-owning) pointers to sprites. */
    using SpriteRefs = std::vector<const Sprite*>;

    /* Static constructor. */
    static SpriteTable Create();

    /* Read a byte from the provided address in OAM. */
    u8 Read(u16 address) const;

    /* Write a byte to the provided address in OAM. */
    void Write(u16 address, u8 byte);

    /*
     * Returns a list of (non-owning) pointers to sprites that needs to be rendered.
     * The list is affected by the current scanline and sprite size setting.
     */
    SpriteRefs GetSpritesToRender(uint line, SpriteSize size) const;
private:
    SpriteTable_();
    std::vector<Sprite> sprites;
};

}
