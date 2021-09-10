#pragma once
#include "interrupt.h"
#include "sprite_table.h"
#include "tile_banks.h"
#include "tile_maps.h"
#include "types.h"

namespace gb {

class LcdControl {
public:
    LcdControl();
    u8 Read() const;
    void Write(u8 byte);
    bool LcdEnabled() const;
    TileMap WindowMap() const;
    bool WindowEnabled() const;
    TileBank BackgroundBank() const;
    TileMap BackgroundMap() const;
    SpriteSize ObjectSize() const;
    bool ObjectsEnabled() const;
    bool BackgroundEnabled() const;
private:
    u8 lcdc;
};

enum class LcdMode {
    HBlank,
    VBlank,
    Oam,
    Transfer
};

class LcdStat {
public:
    explicit LcdStat(InterruptManager&& interrupts);
    u8 Read(u16 address) const;
    void Write(u16 address, u8 byte, bool allowInterrupts);
    u8 Ly() const;
    LcdMode Mode() const;
    void SetLy(u8 newLy);
    void SetMode(LcdMode mode);
    void Enable();
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
