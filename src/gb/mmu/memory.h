#pragma once
#include <cstdint>
#include <vector>
#include "cartridge.h"
#include "input.h"
#include "interrupt.h"
#include "lcd.h"
#include "serial.h"
#include "timer.h"
#include "types.h"

namespace gb {

class Memory {
public:
    Memory(Cartridge cart, Input input, InterruptManager interrupts,
           Lcd lcd, Serial serial, Timer timer);
    u8 Read(std::uint16_t address) const;
    void Write(std::uint16_t address, u8 byte);
private:
    using MemBlock = std::vector<u8>;
    bool BootRomEnabled() const;
    u8 ReadIo(std::uint16_t address) const;
    void WriteIo(std::uint16_t address, u8 byte);
    void DmaTransfer(u8 byte);
    Cartridge cart;
    Input input;
    InterruptManager interrupts;
    Lcd lcd;
    Serial serial;
    Timer timer;
    MemBlock boot;
    MemBlock wram;
    MemBlock hram;
    u8 dma;
    u8 bank;
};

}
