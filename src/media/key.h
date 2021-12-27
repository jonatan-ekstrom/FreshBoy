#pragma once

struct SDL_KeyboardEvent;

namespace sdl {

/* Represents a key press. Created from an SDL_KeyboardEvent.*/
class Key {
public:
    explicit Key(const SDL_KeyboardEvent& event);

    /* The key code. Only keys used by the Game Boy emulator are supported. */
    enum class Code {
        Unknown,
        Up,
        Down,
        Left,
        Right,
        Z,
        X,
        C,
        Backspace,
        Return
    } Code;

    /* The type of key event (up or down). */
    enum class Type {
        Unknown,
        Up,
        Down
    } Type;

    /* The current state of the key (pressed or released) */
    enum class State {
        Unknown,
        Pressed,
        Released
    } State;

    /* True if this is a repeated event. */
    bool Repeat;
};

}
