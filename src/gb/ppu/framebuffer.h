#pragma once
#include <cstdint>
#include <vector>
#include "color.h"
#include "types.h"

namespace gb {

class Framebuffer {
public:
    using Scanline = std::vector<Dot>;
    using Pixels = std::vector<u32>;
    Framebuffer();
    const Pixels& Buffer() const;
    void WriteLine(const Scanline& line, uint index);
    static Scanline GetScreenLine();
private:
    Pixels buffer;
};

}
