#include "memory.h"
#include <stdexcept>
#include <utility>
#include "boot.h"

namespace gb {

Memory::Memory(Cartridge cart, Lcd lcd)
    : cart{std::move(cart)},
      lcd{std::move(lcd)},
      boot{dmg::BootRom.cbegin(), dmg::BootRom.cend()},
      wram(0x2000),
      hram(0x7F),
      dma{0},
      bank{0} {}

std::uint8_t Memory::Read(const std::uint16_t address) const {
    // Boot ROM / Cartridge
    if (address <= 0xFF) {
        if (BootRomEnabled()) {
            return this->boot[address];
        } else {
            return this->cart->Read(address);
        }
    }

    // Cartridge ROM
    if (address <= 0x7FFF) {
        return this->cart->Read(address);
    }

    // VRAM
    if (address >= 0x8000 && address <= 0x9FFF) {
        return this->lcd->Read(address);
    }

    // Cartridge RAM
    if (address >= 0xA000 && address <=0xBFFF) {
        return this->cart->Read(address);
    }

    // WRAM
    if (address >= 0xC000 && address <= 0xDFFF) {
        return this->wram[address - 0xC000];
    }

    // Invalid
    if (address >= 0xE000 && address <= 0xFDFF) {
        throw std::runtime_error{"MMU - invalid read address."};
    }

    // OAM
    if (address >= 0xFE00 && address <= 0xFE9F) {
        return this->lcd->Read(address);
    }

    // Invalid
    if (address >= 0xFEA0 && address <= 0xFEFF) {
        throw std::runtime_error{"MMU - invalid read address."};
    }

    // I/O
    if (address >= 0xFF00 && address <= 0xFF7F) {
        return ReadIo(address);
    }

    // HRAM
    if (address >= 0xFF80 && address <= 0xFFFE) {
        return this->hram[address - 0xFF80];
    }

    if (address == 0xFFFF) {
        return 0; // TODO - Interrupt handler.
    }

    throw std::runtime_error{"MMU - invalid read address."};
}

void Memory::Write(const std::uint16_t address, const std::uint8_t byte) {
    // Boot ROM / Cartridge
    if (address <= 0xFF) {
        if (BootRomEnabled()) {
            throw std::runtime_error{"MMU - invalid write address."};
        } else {
            this->cart->Write(address, byte);
            return;
        }
    }

    // Cartridge ROM
    if (address <= 0x7FFF) {
        this->cart->Write(address, byte);
        return;
    }

    // VRAM
    if (address >= 0x8000 && address <= 0x9FFF) {
        this->lcd->Write(address, byte);
        return;
    }

    // Cartridge RAM
    if (address >= 0xA000 && address <=0xBFFF) {
        this->cart->Write(address, byte);
        return;
    }

    // WRAM
    if (address >= 0xC000 && address <= 0xDFFF) {
        this->wram[address - 0xC000] = byte;
        return;
    }

    // Invalid
    if (address >= 0xE000 && address <= 0xFDFF) {
        throw std::runtime_error{"MMU - invalid write address."};
    }

    // OAM
    if (address >= 0xFE00 && address <= 0xFE9F) {
        this->lcd->Write(address, byte);
        return;
    }

    // Invalid
    if (address >= 0xFEA0 && address <= 0xFEFF) {
        throw std::runtime_error{"MMU - invalid write address."};
    }

    // I/O
    if (address >= 0xFF00 && address <= 0xFF7F) {
        WriteIo(address, byte);
        return;
    }

    // HRAM
    if (address >= 0xFF80 && address <= 0xFFFE) {
        this->hram[address - 0xFF80] = byte;
        return;
    }

    if (address == 0xFFFF) {
        return; // TODO - Interrupt handler.
    }

    throw std::runtime_error{"MMU - invalid write address."};
}

}

bool gb::Memory::BootRomEnabled() const {
    return this->bank == 0;
}

std::uint8_t gb::Memory::ReadIo(const std::uint16_t address) const {
    // Input
    if (address == 0xFF00) {
        return 0; // TODO - Input
    }

    // Serial
    if (address >= 0xFF01 && address <= 0xFF02) {
        return 0; // TODO - Serial
    }

    // Timer
    if (address >= 0xFF04 && address <= 0xFF07) {
        return 0; // TODO - Timer
    }

    // Interrupt
    if (address == 0xFF0F) {
        return 0; // TODO - Interrupt
    }

    // APU
    if (address >= 0xFF10 && address <= 0xFF26) {
        return 0; // TODO - APU
    }

    // LCD
    if (address >= 0xFF40 && address <= 0xFF45) {
        return this->lcd->Read(address);
    }

    // DMA
    if (address == 0xFF46) {
        return this->dma;
    }

    // LCD
    if (address >= 0xFF47 && address <= 0xFF4B) {
        return this->lcd->Read(address);
    }

    // BANK
    if (address == 0xFF50) {
        return this->bank;
    }

    throw std::runtime_error{"MMU - invalid read address"};
}

void gb::Memory::WriteIo(const std::uint16_t address, const std::uint8_t byte) {
    // Input
    if (address == 0xFF00) {
        return; // TODO - Input
    }

    // Serial
    if (address >= 0xFF01 && address <= 0xFF02) {
        return; // TODO - Serial
    }

    // Timer
    if (address >= 0xFF04 && address <= 0xFF07) {
        return; // TODO - Timer
    }

    // Interrupt
    if (address == 0xFF0F) {
        return; // TODO - Interrupt
    }

    // APU
    if (address >= 0xFF10 && address <= 0xFF26) {
        return; // TODO - APU
    }

    // LCD
    if (address >= 0xFF40 && address <= 0xFF45) {
        this->lcd->Write(address, byte);
        return;
    }

    // DMA
    if (address == 0xFF46) {
        DmaTransfer(byte);
        return;
    }

    // LCD
    if (address >= 0xFF47 && address <= 0xFF4B) {
        this->lcd->Write(address, byte);
        return;
    }

    // BANK
    if (address == 0xFF50) {
        this->bank = byte;
        return;
    }

    throw std::runtime_error{"MMU - invalid write address"};
}

void gb::Memory::DmaTransfer(const std::uint8_t byte) {
    constexpr auto numBytes{160};
    std::uint16_t src{static_cast<uint16_t>(byte * 0x100)};
    std::uint16_t dst{0xFE00};
    for (auto i{0}; i < numBytes; ++i) {
        this->lcd->Write(dst++, Read(src++));
    }
    this->dma = byte;
}
