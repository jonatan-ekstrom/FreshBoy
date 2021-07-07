#pragma once

class SDL_KeyboardEvent;

namespace sdl {

class Key {
public:
    explicit Key(const SDL_KeyboardEvent& event);

    enum class Code {
        Unknown,
        Up,
        Down,
        Left,
        Right
    } Code;

    enum class Type {
        Unknown,
        Up,
        Down
    } Type;

    enum class State {
        Unknown,
        Pressed,
        Released
    } State;

    bool Repeat;
};

}
