#pragma once
#include "types.h"

namespace gb {

class Dac {
public:
    Dac();
    void Enable(bool on);
    double Map(u8 sample);
private:
    bool enabled;
};

}
