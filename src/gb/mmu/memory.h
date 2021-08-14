#pragma once
#include <cstdint>
#include <vector>
#include "cartridge.h"
#include "input.h"
#include "interrupt.h"
#include "lcd.h"
#include "serial.h"
#include "timer.h"

namespace gb {

class Memory {
public:
    Memory(Cartridge cart, Input input, InterruptManager interrupts,
           Lcd lcd, Serial serial, Timer timer);
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t byte);
private:
    using MemBlock = std::vector<std::uint8_t>;
    bool BootRomEnabled() const;
    std::uint8_t ReadIo(std::uint16_t address) const;
    void WriteIo(std::uint16_t address, std::uint8_t byte);
    void DmaTransfer(uint8_t byte);
    Cartridge cart;
    Input input;
    InterruptManager interrupts;
    Lcd lcd;
    Serial serial;
    Timer timer;
    MemBlock boot;
    MemBlock wram;
    MemBlock hram;
    std::uint8_t dma;
    std::uint8_t bank;
};

}
