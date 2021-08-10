#pragma once
#include <cstdint>
#include <functional>
#include "sprite_table.h"
#include "tile_banks.h"
#include "tile_maps.h"

namespace gb {

class LcdControl {
public:
    LcdControl();
    std::uint8_t Read() const;
    void Write(std::uint8_t byte);
    bool LcdEnabled() const;
    TileMap WindowMap() const;
    bool WindowEnabled() const;
    TileBank BackgroundBank() const;
    TileMap BackgroundMap() const;
    SpriteSize ObjectSize() const;
    bool ObjectsEnabled() const;
    bool BackgroundEnabled() const;
private:
    std::uint8_t lcdc;
};

enum class LcdMode {
    HBlank,
    VBlank,
    Oam,
    Transfer
};

class LcdStat {
public:
    using InterruptHandler = std::function<void(void)>;
    LcdStat(const InterruptHandler& blankHandler,
            const InterruptHandler& statHandler);
    LcdMode Mode() const;
    std::uint8_t Ly() const;
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
    void SetMode(LcdMode mode);
    void SetLy(std::uint8_t newLy);
private:
    void Refresh();
    void SetLyFlag(bool flag);
    bool UpdateBlankLine();
    bool UpdateStatLine();
    void FireBlank() const;
    void FireStat() const;
    InterruptHandler blankHandler;
    InterruptHandler statHandler;
    bool blankLine;
    bool statLine;
    std::uint8_t stat;
    std::uint8_t ly;
    std::uint8_t lyc;
};

}
