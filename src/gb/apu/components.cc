#include "components.h"
#include "bits.h"

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

Mixer::Mixer() : mask{0} {}

u8 Mixer::Read() const {
    return mask;
}

void Mixer::Write(const u8 byte) {
    this->mask = byte;
}

std::tuple<double, double> Mixer::Mix(const double ch1, const double ch2,
                                      const double ch3, const double ch4) const {
    double left{0};
    double right{0};

    // Mix
    if (bit::IsSet(this->mask, 7)) left += ch4;
    if (bit::IsSet(this->mask, 6)) left += ch3;
    if (bit::IsSet(this->mask, 5)) left += ch2;
    if (bit::IsSet(this->mask, 4)) left += ch1;
    if (bit::IsSet(this->mask, 3)) right += ch4;
    if (bit::IsSet(this->mask, 2)) right += ch3;
    if (bit::IsSet(this->mask, 1)) right += ch2;
    if (bit::IsSet(this->mask, 0)) right += ch1;

    // Normalize
    left /= 4;
    right /= 4;

    return {left, right};
}

}
