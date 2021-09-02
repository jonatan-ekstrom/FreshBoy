#pragma once
#include "tone.h"

namespace gb {

class Sweep : public ToneBase {
public:
    Sweep();
    void SweepTick();
};

}
