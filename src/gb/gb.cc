#include "gb.h"
#include <tuple>
#include <utility>
#include "log.h"

namespace {

using gb::Path;
auto GetRamPath(const Path& romPath, const Path& ramPath) {
    const auto suggested{ramPath.empty() ? Path{romPath}.replace_extension("ram") : ramPath};
    return std::make_tuple(suggested, exists(suggested));
}

}

namespace gb {

Gameboy_::Gameboy_(const Path& romPath, const Path& ramPath,
                   FrameCallback&& render, QueueCallback&& queue,
                   const uint sampleRate, const bool log)
    : cart{Cartridge_::Create(romPath)},
      apu{Apu_::Create(std::move(queue), sampleRate)},
      interrupts{InterruptManager_::Create()},
      input{Input_::Create(this->interrupts)},
      serial{Serial_::Create(this->interrupts)},
      timer{Timer_::Create(this->interrupts)},
      ppu{Lcd_::Create(this->interrupts, std::move(render))},
      mmu{Memory_::Create(this->cart, this->input, this->interrupts,
                          this->ppu, this->serial, this->apu, this->timer)},
      cpu{Cpu_::Create(this->interrupts, this->mmu)} {
    // Enable logging if requested.
    if (log) log::Enable();

    // Save a path to the ram file on disk. Load it if available.
    const auto [ram, available] = GetRamPath(romPath, ramPath);
    this->ramPath = ram;
    if (available) {
        this->cart->LoadRam(this->ramPath);
    }
}

Gameboy Gameboy_::Create(const Path& romPath, const Path& ramPath,
                         FrameCallback render, QueueCallback queue,
                         const uint sampleRate,
                         const bool log) {
    return Gameboy{new Gameboy_{romPath, ramPath,
                                std::move(render), std::move(queue),
                                sampleRate, log}};
}

std::string Gameboy_::Header() const {
    return this->cart->HeaderInfo();
}

void Gameboy_::Run(const ContinueCallback& cont) {
    // Run the emulation until 'cont' returns false.
    while (cont()) {
        Tick();
    }
    // Save the cartridge RAM to disk.
    this->cart->SaveRam(this->ramPath);
}

void Gameboy_::ButtonPressed(const Button button) {
    this->input->PressButton(button);
}

void Gameboy_::ButtonReleased(const Button button) {
    this->input->ReleaseButton(button);
}

void Gameboy_::NextColorMap() {
    this->ppu->NextColorMap();
}

void Gameboy_::Tick() {
    // Run the next instruction.
    const auto cycles{this->cpu->Tick()};

    // Synchronize each subsystem.
    this->apu->Tick(cycles);
    this->cart->Tick(cycles);
    this->serial->Tick(cycles);
    this->timer->Tick(cycles);
    this->ppu->Tick(cycles);
}

}
