#pragma once
#include "types.h"

namespace gb::lcd {

/* The LCD width in pixels. */
inline constexpr uint DisplayWidth{160};

/* The LCD height in pixels. */
inline constexpr uint DisplayHeight{144};

/* CPU cycles per second. */
inline constexpr uint ClockFreq{4194304};

/* Number of CPU cycles per screen refresh (on average). */
inline constexpr uint CyclesPerFrame{70224};

}
