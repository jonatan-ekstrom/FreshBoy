#include "gb.h"
#include "log.h"

namespace gb {

Gameboy_::Gameboy_(const std::string& filePath, const RenderCallback& render,
                   const QueueCallback& queue, const bool log)
    : render{render},
      queue{queue},
      cart{Cartridge_::Create(filePath)},
      apu{Apu_::Create()},
      interrupts{InterruptManager_::Create()},
      input{Input_::Create(this->interrupts)},
      serial{Serial_::Create(this->interrupts)},
      timer{Timer_::Create(this->interrupts)},
      ppu{Lcd_::Create(this->interrupts, [this] (const auto& pixels) { FrameReady(pixels); })},
      mmu{Memory_::Create(this->cart, this->input, this->interrupts,
                          this->ppu, this->serial, this->apu, this->timer)},
      cpu{Cpu_::Create(this->interrupts, this->mmu)} {
    if (log) log::Enable();
}

Gameboy Gameboy_::Create(const std::string& filePath,
                         const RenderCallback& render,
                         const QueueCallback& queue,
                         const bool log) {
    return Gameboy{new Gameboy_{filePath, render, queue, log}};
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
    this->serial->Tick(cycles);
    this->timer->Tick(cycles);
    this->ppu->Tick(cycles);
}

void Gameboy_::FrameReady(const Framebuffer::Pixels& pixels) {
    const auto left{this->apu->SampleLeft()};
    const auto right{this->apu->SampleRight()};
    queue(left, right);
    render(pixels);
}

}
