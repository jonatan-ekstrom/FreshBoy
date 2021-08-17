#include "memory.h"
#include <stdexcept>
#include <utility>
#include "boot.h"

namespace gb {

Memory_::Memory_(Cartridge&& cart, Input&& input, InterruptManager&& interrupts,
                 Lcd&& lcd, Serial&& serial, Sound&& sound, Timer&& timer)
    : cart{std::move(cart)},
      input{std::move(input)},
      interrupts{std::move(interrupts)},
      lcd{std::move(lcd)},
      serial{std::move(serial)},
      sound{std::move(sound)},
      timer{std::move(timer)},
      boot{dmg::BootRom.cbegin(), dmg::BootRom.cend()},
      wram(0x2000),
      hram(0x7F),
      dma{0},
      bank{0} {}

Memory Memory_::Create(Cartridge cart, Input input, InterruptManager interrupts,
                      Lcd lcd, Serial serial, Sound sound, Timer timer) {
    return Memory{new Memory_{std::move(cart), std::move(input),
                              std::move(interrupts), std::move(lcd),
                              std::move(serial), std::move(sound),
                              std::move(timer)}};
}

u8 Memory_::Read(const u16 address) const {
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

    // IE
    if (address == 0xFFFF) {
        return this->interrupts->Read(address);
    }

    throw std::runtime_error{"MMU - invalid read address."};
}

void Memory_::Write(const u16 address, const u8 byte) {
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

    // IE
    if (address == 0xFFFF) {
        this->interrupts->Write(address, byte);
        return;
    }

    throw std::runtime_error{"MMU - invalid write address."};
}

bool Memory_::BootRomEnabled() const {
    return this->bank == 0;
}

u8 Memory_::ReadIo(const u16 address) const {
    // Input
    if (address == 0xFF00) {
        return this->input->Read();
    }

    // Serial
    if (address >= 0xFF01 && address <= 0xFF02) {
        return this->serial->Read(address);
    }

    // Timer
    if (address >= 0xFF04 && address <= 0xFF07) {
        return this->timer->Read(address);
    }

    // IF
    if (address == 0xFF0F) {
        return this->interrupts->Read(address);
    }

    // APU
    if (address >= 0xFF10 && address <= 0xFF3F) {
        return this->sound->Read(address);
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

void Memory_::WriteIo(const u16 address, const u8 byte) {
    // Input
    if (address == 0xFF00) {
        this->input->Write(byte);
        return;
    }

    // Serial
    if (address >= 0xFF01 && address <= 0xFF02) {
        this->serial->Write(address, byte);
        return;
    }

    // Timer
    if (address >= 0xFF04 && address <= 0xFF07) {
        this->timer->Write(address, byte);
        return;
    }

    // IF
    if (address == 0xFF0F) {
        this->interrupts->Write(address, byte);
        return;
    }

    // APU
    if (address >= 0xFF10 && address <= 0xFF3F) {
        this->sound->Write(address, byte);
        return;
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

void Memory_::DmaTransfer(const u8 byte) {
    constexpr auto numBytes{160};
    u16 src{static_cast<u16>(byte * 0x100)};
    if (src < 0x8000 || src > 0xDFFF) {
        throw std::runtime_error{"MMU - invalid DMA transfer source."};
    }
    u16 dst{0xFE00};
    for (auto i{0}; i < numBytes; ++i) {
        this->lcd->Write(dst++, Read(src++));
    }
    this->dma = byte;
}

}
