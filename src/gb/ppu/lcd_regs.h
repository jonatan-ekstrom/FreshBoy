#pragma once
#include "interrupt.h"
#include "sprite_table.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "types.h"

namespace gb {

/* Class representing the LCDC (LCD control register). */
class LcdControl {
public:
    /* Creates a new instance of the LCDC. */
    LcdControl();

    /* Read the data in the register. */
    u8 Read() const;

    /* Write data to the register. */
    void Write(u8 byte);

    /* Returns true if the LCD is enabled. */
    bool LcdEnabled() const;

    /* Returns the currently selected tile map being used by the window. */
    TileMap WindowMap() const;

    /* Returns true if the window is enabled. */
    bool WindowEnabled() const;

    /* Returns the currently selected tile bank used by the background and window. */
    TileBank BackgroundBank() const;

    /* Returns the currently selected tile map being used by the background. */
    TileMap BackgroundMap() const;

    /* Returns the currently selected sprite size. */
    SpriteSize ObjectSize() const;

    /* Returns true if objects (sprites) are enabled. */
    bool ObjectsEnabled() const;

    /* Returns true if the background is enabled. */
    bool BackgroundEnabled() const;
private:
    u8 lcdc;
};

/* Enumeration of the LCD modes of operation. */
enum class LcdMode {
    HBlank,
    VBlank,
    Oam,
    Transfer
};

/*
 * Class representing the STAT (LCD status register).
 * It also manages the LY and LYC registers.
 */
class LcdStat {
public:
    /* Creates a new instance of the STAT register. */
    explicit LcdStat(InterruptManager&& interrupts);

    /* Reads a byte of data from the specified address. */
    u8 Read(u16 address) const;

    /* Writes a byte of data to the provided address, optionally allowing interrupts. */
    void Write(u16 address, u8 byte, bool allowInterrupts);

    /* Returns the current scanline, i.e. the value of the LY register. */
    u8 Ly() const;

    /* Returns the current mode of operation. */
    LcdMode Mode() const;

    /* Changes the active scanline, i.e the LY register. */
    void SetLy(u8 newLy);

    /* Changes the mode of operation. */
    void SetMode(LcdMode mode);

    /* Called when the LCD is enabled. */
    void Enable();

    /* Called when the LCD is disabled. */
    void Disable();
private:
    void Refresh(bool allowInterrupts = true);
    bool UpdateBlankLine();
    bool UpdateStatLine();
    void FireBlank() const;
    void FireStat() const;
    InterruptManager interrupts;
    bool blankLine;
    bool statLine;
    u8 stat;
    u8 ly;
    u8 lyc;
};

}
