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
    void WriteLine(const Scanline& line, unsigned int index);
    const Pixels& Buffer() const;
private:
    Pixels buffer;
};

}
