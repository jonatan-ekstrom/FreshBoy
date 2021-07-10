#include "demo.h"
#include <algorithm>
#include <iostream>
#include "key.h"
#include "header.h"

using namespace sdl;

namespace gb {

Demo::Demo()
    : running{false},
      instance{Instance_::Create()},
      eventManager{this->instance},
      window{Window_::Create(this->instance, "Demo Window", 600, 400)},
      renderer{Renderer_::Create(this->instance, this->window)},
      texture{this->instance, this->renderer, 160, 144} {
    eventManager.RegisterKeyHandler([this] (const Key& key) { this->KeyHandler(key); });
    eventManager.RegisterQuitHandler([this] { this->QuitHandler(); });
}

void Demo::Run() {
    //this->running = true;
    //this->window->Show();
    //while (this->running) {
    //    this->eventManager.WaitForEvent();
    //}

    const gb::Header header{"/home/jonatan/Desktop/zelda.gb"};
    std::cout << header.PrettyPrint() << std::endl;
}

void Demo::KeyHandler(const Key& key) {
    if (key.Repeat) return;
    if (key.Type != Key::Type::Down) return;
    switch (key.Code) {
        case Key::Code::Up:
            Draw(Texture::Pixel(255, 0, 0, 255));
            break;
        case Key::Code::Down:
            Draw(Texture::Pixel(255, 255, 0, 255));
            break;
        case Key::Code::Left:
            Draw(Texture::Pixel(0, 255, 0, 255));
            break;
        case Key::Code::Right:
            Draw(Texture::Pixel(0, 0, 255, 255));
            break;
        case Key::Code::Z:
        case Key::Code::X:
        case Key::Code::Backspace:
        case Key::Code::Return:
        case Key::Code::Unknown:
        default:
            break;
    }
}

void Demo::QuitHandler() {
    this->running = false;
}

void Demo::Draw(const std::uint32_t color) {
    const auto pixels{this->texture.Lock()};
    const auto size{texture.Width() * texture.Height()};
    std::fill(pixels, pixels + size, color);
    this->texture.Unlock();
    this->renderer->Clear();
    this->renderer->Copy(this->texture);
    this->renderer->Present();
}

}
