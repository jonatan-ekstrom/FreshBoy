#pragma once
#include <tuple>
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

class Mixer {
public:
    Mixer();
    u8 Read() const;
    void Write(u8 byte);
    std::tuple<double, double> Mix(double ch1, double ch2,
                                   double ch3, double ch4) const;
private:
    u8 mask;
};

}
