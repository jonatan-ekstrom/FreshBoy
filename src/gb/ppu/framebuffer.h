#pragma once
#include <cstdint>
#include <vector>
#include "color.h"

namespace gb {

class Framebuffer {
public:
    using Scanline = std::vector<Dot>;
    using Pixels = std::vector<std::uint32_t>;
    Framebuffer();
    const Pixels& Buffer() const;
    void WriteLine(const Scanline& line, unsigned int index);
    static Scanline GetScreenLine();
private:
    Pixels buffer;
};

}
