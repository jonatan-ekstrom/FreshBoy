#include "lcd.h"
#include <stdexcept>

namespace gb {

Lcd Lcd_::Create() {
    return Lcd{new Lcd_{}};
}

Lcd_::Lcd_()
    : banks{TileBanks_::Create()},
      maps{TileMaps_::Create()},
      table{SpriteTable_::Create()},
      palettes{},
      bg{this->banks,
         this->maps,
         this->palettes.Background()},
      window{this->banks,
             this->maps,
             this->palettes.Background()},
      sprites{this->banks,
              this->table,
              this->palettes.Object0(),
              this->palettes.Object1()},
      lcdc{},
      stat{[this] { StatInterrupt(); }} {}

std::uint8_t Lcd_::Read(const std::uint16_t address) const {
    // Tile banks
    if (address >= 0x8000 && address <= 0x97FF) {
        return this->banks->Read(address);
    }

    // Tile maps
    if (address >= 0x9800 && address <= 0x9FFF) {
        return this->maps->Read(address);
    }

    // OAM
    if (address >= 0xFE00 && address <= 0xFE9F) {
        return this->table->Read(address);
    }

    // LCDC
    if (address == 0xFF40) {
        return this->lcdc.Read();
    }

    // STAT
    if (address == 0xFF41) {
        return this->stat.Read(address);
    }

    // SCX & SCY
    if (address >= 0xFF42 && address <= 0xFF43) {
        return this->bg.Read(address);
    }

    // LY & LYC
    if (address >= 0xFF44 && address <= 0xFF45) {
        return this->stat.Read(address);
    }

    // Palettes
    if (address >= 0xFF47 && address <= 0xFF49) {
        return this->palettes.Read(address);
    }

    // WX & WY
    if (address >= 0xFF4A && address <= 0xFF4B) {
        return this->window.Read(address);
    }

    throw std::runtime_error{"LCD - Invalid read address."};
}

void Lcd_::Write(const std::uint16_t address, const std::uint8_t byte) {
    // Tile banks
    if (address >= 0x8000 && address <= 0x97FF) {
        this->banks->Write(address, byte);
        return;
    }

    // Tile maps
    if (address >= 0x9800 && address <= 0x9FFF) {
        this->maps->Write(address, byte);
        return;
    }

    // OAM
    if (address >= 0xFE00 && address <= 0xFE9F) {
        this->table->Write(address, byte);
        return;
    }

    // LCDC
    if (address == 0xFF40) {
        this->lcdc.Write(byte);
        return;
    }

    // STAT
    if (address == 0xFF41) {
        this->stat.Write(address, byte);
        return;
    }

    // SCX & SCY
    if (address >= 0xFF42 && address <= 0xFF43) {
        this->bg.Write(address, byte);
        return;
    }

    // LYC
    if (address == 0xFF45) {
        this->stat.Write(address, byte);
        return;
    }

    // Palettes
    if (address >= 0xFF47 && address <= 0xFF49) {
        this->palettes.Write(address, byte);
        return;
    }

    // WX & WY
    if (address >= 0xFF4A && address <= 0xFF4B) {
        this->window.Write(address, byte);
        return;
    }

    throw std::runtime_error{"LCD - Invalid write address."};
}

void Lcd_::StatInterrupt() {}

}
