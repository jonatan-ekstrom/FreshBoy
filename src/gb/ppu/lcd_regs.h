#pragma once
#include <cstdint>
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
    LcdMode Mode() const;
    u8 Ly() const;
    u8 Read(std::uint16_t address) const;
    void Write(std::uint16_t address, u8 byte);
    void SetMode(LcdMode mode);
    void SetLy(u8 newLy);
private:
    void Refresh();
    void SetLyFlag(bool flag);
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
