#pragma once
#include <memory>
#include <vector>
#include "cartridge.h"
#include "input.h"
#include "interrupt.h"
#include "lcd.h"
#include "serial.h"
#include "apu.h"
#include "timer.h"
#include "types.h"

namespace gb {

class Memory_;
using Memory = std::shared_ptr<Memory_>;

/* Class representing the Memory Management Unit (MMU). */
class Memory_ {
public:
    /* Static constructor. */
    static Memory Create(Cartridge cart, Input input, InterruptManager interrupts,
                         Lcd lcd, Serial serial, Apu sound, Timer timer);

    /* Read one byte from the provided address. */
    u8 Read(u16 address) const;

    /* Write one byte to the provided address. */
    void Write(u16 address, u8 byte);
private:
    using MemBlock = std::vector<u8>;
    Memory_(Cartridge&& cart, Input&& input, InterruptManager&& interrupts,
            Lcd&& lcd, Serial&& serial, Apu&& sound, Timer&& timer);
    bool BootRomEnabled() const;
    u8 ReadIo(u16 address) const;
    void WriteIo(u16 address, u8 byte);
    void DmaTransfer(u8 byte);
    Cartridge cart;
    Input input;
    InterruptManager interrupts;
    Lcd lcd;
    Serial serial;
    Apu sound;
    Timer timer;
    MemBlock boot;
    MemBlock wram;
    MemBlock hram;
    u8 dma;
    u8 bank;
};

}
