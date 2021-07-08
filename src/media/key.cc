#include "key.h"
#include <SDL_events.h>
#include <SDL_keycode.h>

namespace sdl {

Key::Key(const SDL_KeyboardEvent& event)
    : Code{}, Type{}, State{}, Repeat{event.repeat != 0} {
    switch (event.keysym.sym) {
        case SDLK_UP:
            Code = Code::Up;
            break;
        case SDLK_DOWN:
            Code = Code::Down;
            break;
        case SDLK_LEFT:
            Code = Code::Left;
            break;
        case SDLK_RIGHT:
            Code = Code::Right;
            break;
        case SDLK_z:
            Code = Code::Z;
            break;
        case SDLK_x:
            Code = Code::X;
            break;
        case SDLK_BACKSPACE:
            Code = Code::Backspace;
            break;
        case SDLK_RETURN:
            Code = Code::Return;
            break;
        default:
            break;
    }

    switch (event.type) {
        case SDL_KEYUP:
            Type = Type::Up;
            break;
        case SDL_KEYDOWN:
            Type = Type::Down;
            break;
        default:
            break;
    }

    switch (event.state) {
        case SDL_PRESSED:
            State = State::Pressed;
            break;
        case SDL_RELEASED:
            State = State::Released;
            break;
        default:
            break;
    }
}

}
