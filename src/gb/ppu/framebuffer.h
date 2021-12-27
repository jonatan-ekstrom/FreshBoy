#pragma once
#include <vector>
#include "color.h"
#include "dot.h"
#include "types.h"

namespace gb {

/* Stores all pixel data currently being rendered by the PPU. */
class FrameBuffer {
public:
    /* Typedef for pixel data. Data is stored as 32-bit pixels (RGBA). */
    using Pixels = std::vector<u32>;

    /* Creates a new instance of the frame buffer. */
    explicit FrameBuffer(ColorMaps maps);

    /* Lock the current frame for rendering and retrieve a reference to the pixel data. */
    const Pixels& LockFrame();

    /* Return a pointer to the scanline referenced by the provided row index. */
    Dot* ScanlinePtr(uint rowIndex);

    /* Resets the frame buffer to its initial state. */
    void Reset();
private:
    u32 DotToPixel(const Dot& dot) const;
    u32 ScreenPixel() const;
    ColorMaps maps;
    std::vector<Dot> dots;
    Pixels pixels;
};

}
