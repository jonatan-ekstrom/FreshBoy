#pragma once
#include <functional>
#include <memory>
#include <string>
#include "apu.h"
#include "cartridge.h"
#include "cpu.h"
#include "input.h"
#include "interrupt.h"
#include "lcd.h"
#include "memory.h"
#include "serial.h"
#include "timer.h"
#include "types.h"

namespace gb {

class Gameboy_;
using Gameboy = std::unique_ptr<Gameboy_>;

class Gameboy_ {
public:
    using ContinueCallback = std::function<bool(void)>;
    using FrameCallback = Lcd_::FrameHandler;
    using QueueCallback = Apu_::QueueHandler;
    static Gameboy Create(const std::string& filePath, const FrameCallback& render,
                          const QueueCallback& queue, bool log = false);
    std::string Header() const;
    void Run(const ContinueCallback& cont);
    void ButtonPressed(Button button);
    void ButtonReleased(Button button);
private:
    Gameboy_(const std::string& filePath, const FrameCallback& render,
             const QueueCallback& queue, bool log);
    void Tick();
    Cartridge cart;
    Apu apu;
    InterruptManager interrupts;
    Input input;
    Serial serial;
    Timer timer;
    Lcd ppu;
    Memory mmu;
    Cpu cpu;
};

}
