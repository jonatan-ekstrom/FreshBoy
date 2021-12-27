#pragma once
#include <vector>
#include "dot.h"
#include "types.h"

namespace gb {

/* Stores all pixel data currently being rendered by the PPU. */
class FrameBuffer {
public:
    /* Typedef for pixel data. Data is stored as 32-bit pixels (RGBA). */
    using Pixels = std::vector<u32>;

    /* Creates a new instance of the frame buffer. */
    FrameBuffer();

    /* Lock the current frame for rendering and retrieve a reference to the pixel data. */
    const Pixels& LockFrame();

    /* Return a pointer to the scanline referenced by the provided row index. */
    Dot* ScanlinePtr(uint rowIndex);

    /* Resets the frame buffer to its initial state. */
    void Reset();
private:
    std::vector<Dot> dots;
    Pixels pixels;
};

}
