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
#include "path.h"
#include "serial.h"
#include "timer.h"
#include "types.h"

namespace gb {

class Gameboy_;
using Gameboy = std::unique_ptr<Gameboy_>;

/*
 * Top level class assembling all Game Boy subsystems.
 */
class Gameboy_ {
public:
    using ContinueCallback = std::function<bool(void)>;
    using FrameCallback = Lcd_::FrameHandler;
    using QueueCallback = Apu_::QueueHandler;

    /*
     * Static constructor, creates a new Game Boy instance.
     * Loads the provided rom / ram files.
     * Sets up rendering and sound using the provided callbacks,
     * screen refresh rate and sound sample rate.
     */
    static Gameboy Create(const Path& romPath, const Path& ramPath,
                          FrameCallback render, QueueCallback queue,
                          uint refreshRate, uint sampleRate, bool log = false);

    /* Returns a string representation of the ROM header. */
    std::string Header() const;

    /* Run the emulator until the 'cont' callback returns false. */
    void Run(const ContinueCallback& cont);

    /* Set the state of the button to pressed. */
    void ButtonPressed(Button button);

    /* Set the state of the button to released. */
    void ButtonReleased(Button button);

    /* Switches to the next available color map for rendering. */
    void NextColorMap();
private:
    Gameboy_(const Path& romPath, const Path& ramPath,
             FrameCallback&& render, QueueCallback&& queue,
             uint refreshRate, uint sampleRate, bool log);
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
    Path ramPath;
};

}
