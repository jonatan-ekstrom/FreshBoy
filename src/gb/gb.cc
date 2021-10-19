#include "gb.h"
#include <tuple>
#include "log.h"

namespace fs = std::filesystem;

namespace {

auto GetRamPath(const fs::path& romPath, const fs::path& ramPath) {
    fs::path suggested{};
    if (!ramPath.empty()) {
        suggested = ramPath;
    } else {
        suggested = fs::path{romPath}.replace_extension("ram");
    }
    return std::make_tuple(suggested, exists(suggested));
}

}

namespace gb {

Gameboy_::Gameboy_(const fs::path& romPath, const fs::path& ramPath,
                   const FrameCallback& render, const QueueCallback& queue,
                   const uint refreshRate, const uint sampleRate, const bool log)
    : cart{Cartridge_::Create(romPath, refreshRate)},
      apu{Apu_::Create(queue, refreshRate, sampleRate)},
      interrupts{InterruptManager_::Create()},
      input{Input_::Create(this->interrupts)},
      serial{Serial_::Create(this->interrupts)},
      timer{Timer_::Create(this->interrupts)},
      ppu{Lcd_::Create(this->interrupts, render)},
      mmu{Memory_::Create(this->cart, this->input, this->interrupts,
                          this->ppu, this->serial, this->apu, this->timer)},
      cpu{Cpu_::Create(this->interrupts, this->mmu)} {
    if (log) log::Enable();
    const auto [ram, available] = GetRamPath(romPath, ramPath);
    this->ramPath = ram;
    if (available) {
        this->cart->LoadRam(this->ramPath);
    }
}

Gameboy Gameboy_::Create(const fs::path& romPath,
                         const fs::path& ramPath,
                         const FrameCallback& render,
                         const QueueCallback& queue,
                         const uint refreshRate,
                         const uint sampleRate,
                         const bool log) {
    return Gameboy{new Gameboy_{romPath, ramPath, render, queue, refreshRate, sampleRate, log}};
}

std::string Gameboy_::Header() const {
    return this->cart->HeaderInfo();
}

void Gameboy_::Run(const ContinueCallback& cont) {
    while (cont()) {
        Tick();
    }
    this->cart->SaveRam(this->ramPath);
}

void Gameboy_::ButtonPressed(const Button button) {
    this->input->PressButton(button);
}

void Gameboy_::ButtonReleased(const Button button) {
    this->input->ReleaseButton(button);
}

void Gameboy_::Tick() {
    const auto cycles{this->cpu->Tick()};
    this->apu->Tick(cycles);
    this->cart->Tick(cycles);
    this->serial->Tick(cycles);
    this->timer->Tick(cycles);
    this->ppu->Tick(cycles);
}

}
