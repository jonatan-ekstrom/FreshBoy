#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace gb { class Gameboy_; }

namespace api {

struct GameboyDeleter { void operator()(gb::Gameboy_* p); };
using Gameboy = std::unique_ptr<gb::Gameboy_, GameboyDeleter>;
using Pixels = std::vector<std::uint32_t>;
using Samples = std::vector<std::uint8_t>;
using ContinueCallback = std::function<bool(void)>;
using RenderCallback = std::function<void(const Pixels&)>;
using QueueCallback = std::function<void(const Samples&, const Samples&)>;
enum class Button { Right, Left, Up, Down, A, B, Select, Start };

Gameboy Create(const std::string& filePath, const RenderCallback& render,
               const QueueCallback& queue, uint refreshRate, const bool log = false);
std::string Header(const Gameboy& gb);
void Run(const Gameboy& gb, const ContinueCallback& cont);
void ButtonPressed(const Gameboy& gb, Button button);
void ButtonReleased(const Gameboy& gb, Button button);

}
