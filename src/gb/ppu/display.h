#pragma once
#include "types.h"

namespace gb::lcd {

/* The LCD display width in pixels. */
inline constexpr uint DisplayWidth{160};

/* The LCD display height in pixels. */
inline constexpr uint DisplayHeight{144};

/* Number of CPU cycles per screen refresh (on average). */
inline constexpr uint CyclesPerFrame{70224};

}
