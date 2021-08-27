#pragma once
#include <vector>
#include "color.h"
#include "types.h"

namespace gb {

class Framebuffer {
public:
    using Pixels = std::vector<u32>;
    Framebuffer();
    const Pixels& LockFrame();
    Dot* ScanlinePtr(uint index);
private:
    std::vector<Dot> dots;
    Pixels pixels;
};

}
