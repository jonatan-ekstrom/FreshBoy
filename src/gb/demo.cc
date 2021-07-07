#include "demo.h"
#include <iostream>
#include "key.h"

using namespace sdl;

namespace { void KeyHandler(const Key&); }

namespace gb {

Demo::Demo()
    : running{false},
      instance{Instance_::Create()},
      window{Window_::Create(this->instance, "Demo Window", 600, 400)},
      eventManager{this->instance} {
    eventManager.RegisterKeyHandler(KeyHandler);
    eventManager.RegisterQuitHandler([this] { this->QuitHandler(); });
}

void Demo::Run() {
    this->running = true;
    this->window->Show();
    while (this->running) {
        this->eventManager.WaitForEvent();
    }
}

void Demo::QuitHandler() {
    this->running = false;
}

}

namespace {

void KeyHandler(const Key& key) {
    if (key.Repeat) return;
    if (key.Type != Key::Type::Down) return;
    switch (key.Code) {
        case Key::Code::Up:
            std::cout << "Up!" << std::endl;
            break;
        case Key::Code::Down:
            std::cout << "Down!" << std::endl;
            break;
        case Key::Code::Left:
            std::cout << "Left!" << std::endl;
            break;
        case Key::Code::Right:
            std::cout << "Right!" << std::endl;
            break;
        case Key::Code::Unknown:
        default:
            break;
    }
}

}
