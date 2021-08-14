#pragma once
#include <cstdint>
#include <vector>
#include "cartridge.h"
#include "interrupt.h"
#include "lcd.h"

namespace gb {

class Memory {
public:
    Memory(Cartridge cart, Lcd lcd, InterruptManager interrupts);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
private:
    using MemBlock = std::vector<std::uint8_t>;
    bool BootRomEnabled() const;
    std::uint8_t ReadIo(std::uint16_t address) const;
    void WriteIo(std::uint16_t address, std::uint8_t byte);
    void DmaTransfer(uint8_t byte);
    Cartridge cart;
    Lcd lcd;
    InterruptManager interrupts;
    MemBlock boot;
    MemBlock wram;
    MemBlock hram;
    std::uint8_t dma;
    std::uint8_t bank;
};

}
