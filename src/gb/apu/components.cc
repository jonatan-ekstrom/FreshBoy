#include "components.h"

namespace gb {

Dac::Dac() : enabled{false} {}

void Dac::Enable(bool on) {
    this->enabled = on;
}

double Dac::Map(const u8 sample) {
    if (!this->enabled) return 0;
    if (sample >= 15) return 1;
    return -1 + 2 * (sample / 15.0);
}

}
