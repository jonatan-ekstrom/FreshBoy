#pragma once
#include <functional>
#include <memory>
#include <string>
#include "apu.h"
#include "cartridge.h"
#include "cpu.h"
#include "framebuffer.h"
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
    using RenderCallback = std::function<void(const Framebuffer::Pixels&)>;
    using QueueCallback = std::function<void(const Apu_::Samples&, const Apu_::Samples&)>;
    static Gameboy Create(const std::string& filePath, const RenderCallback& render,
                          const QueueCallback& queue, bool log = false);
    std::string Header() const;
    void Run(const ContinueCallback& cont);
    void ButtonPressed(Button button);
    void ButtonReleased(Button button);
private:
    Gameboy_(const std::string& filePath, const RenderCallback& render,
             const QueueCallback& queue, bool log);
    void Tick();
    void FrameReady(const Framebuffer::Pixels& pixels);
    RenderCallback render;
    QueueCallback queue;
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
