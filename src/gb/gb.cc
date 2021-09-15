#include "gb.h"
#include "log.h"

namespace gb {

Gameboy_::Gameboy_(const std::string& filePath, const FrameCallback& render,
                   const QueueCallback& queue, const uint refreshRate, const bool log)
    : cart{Cartridge_::Create(filePath, refreshRate)},
      apu{Apu_::Create(queue, refreshRate)},
      interrupts{InterruptManager_::Create()},
      input{Input_::Create(this->interrupts)},
      serial{Serial_::Create(this->interrupts)},
      timer{Timer_::Create(this->interrupts)},
      ppu{Lcd_::Create(this->interrupts, render)},
      mmu{Memory_::Create(this->cart, this->input, this->interrupts,
                          this->ppu, this->serial, this->apu, this->timer)},
      cpu{Cpu_::Create(this->interrupts, this->mmu)} {
    if (log) log::Enable();
}

Gameboy Gameboy_::Create(const std::string& filePath,
                         const FrameCallback& render,
                         const QueueCallback& queue,
                         const uint refreshRate,
                         const bool log) {
    return Gameboy{new Gameboy_{filePath, render, queue, refreshRate, log}};
}

std::string Gameboy_::Header() const {
    return this->cart->HeaderInfo();
}

void Gameboy_::Run(const ContinueCallback& cont) {
    while (cont()) {
        Tick();
    }
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
