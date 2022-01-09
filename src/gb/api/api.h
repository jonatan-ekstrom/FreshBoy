#pragma once
#include <cstdint>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace gb { class Gameboy_; }

/* Public API of the gb static library. */
namespace api {

/* A filesystem path. */
using Path = std::filesystem::path;

/* A collection of pixels (RGBA). */
using Pixels = std::vector<std::uint32_t>;

/* A collection of sound samples. 8-bit unsigned, 44.1 kHz. */
using Samples = std::vector<std::uint8_t>;

/* Function called to determine whether to continue emulating. */
using ContinueCallback = std::function<bool(void)>;

/* Function called to request a new screen render. */
using RenderCallback = std::function<void(const Pixels&)>;

/* Function called to queue up new audio samples. */
using QueueCallback = std::function<void(const Samples&, const Samples&)>;

/* Enumeration of all supported joypad buttons. */
enum class Button { Right, Left, Up, Down, A, B, Select, Start };

/* Display (texture) sizes used by the emulator. */
inline constexpr unsigned int DisplayWidth{160};
inline constexpr unsigned int DisplayHeight{144};

/* Opaque pointer handle. */
class Handle {
public:
    explicit Handle(gb::Gameboy_* handle);
    const gb::Gameboy_* operator->() const;
    gb::Gameboy_* operator->();
private:
    struct GameboyDeleter { void operator()(gb::Gameboy_* p); };
    std::unique_ptr<gb::Gameboy_, GameboyDeleter> handle;
};

/* Public Game Boy API wrapper class. */
class Gameboy {
public:
    /* Constructs a new instance of the Game Boy emulator. */
    Gameboy(const Path& romPath, const Path& ramPath,
            RenderCallback render, QueueCallback queue,
            unsigned int refreshRate, unsigned int sampleRate, bool log);

    /* Returns a dump of the ROM header as a string. */
    std::string Header() const;

    /* Runs the emulation until 'cont' returns false */
    void Run(const ContinueCallback& cont);

    /* Triggers a button press in the emulator. */
    void ButtonPressed(Button button);

    /* Triggers a button release in the emulator. */
    void ButtonReleased(Button button);

    /* Switches to the next available color map for rendering. */
    void NextColorMap();
private:
    Handle gb;
};

}
