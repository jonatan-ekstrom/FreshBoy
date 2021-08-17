#include "gb.h"

namespace gb {

Gameboy_::Gameboy_(const std::string& filePath, const RenderCallback& render)
    : cart{Cartridge_::Create(filePath)},
      interrupts{InterruptManager_::Create()},
      input{Input_::Create(this->interrupts)},
      serial{Serial_::Create(this->interrupts)},
      timer{Timer_::Create(this->interrupts)},
      ppu{Lcd_::Create(this->interrupts, render)},
      apu{Sound_::Create()},
      mmu{Memory_::Create(this->cart, this->input, this->interrupts,
                          this->ppu, this->serial, this->apu, this->timer)} {}

Gameboy Gameboy_::Create(const std::string& filePath,
                         const Gameboy_::RenderCallback& render) {
    return Gameboy{new Gameboy_{filePath, render}};
}

std::string Gameboy_::Header() const {
    return std::string();
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
    constexpr auto cycles{4};

    // TODO - implement CPU.

    this->timer->Tick(cycles);
    this->serial->Tick(cycles);
    this->ppu->Tick(cycles);
}

}
