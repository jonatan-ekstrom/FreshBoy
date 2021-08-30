#pragma once
#include <functional>
#include <tuple>
#include "types.h"

namespace gb {

class Sequencer {
public:
    using Callback = std::function<void(uint)>;
    explicit Sequencer(const Callback& callback);
    void Tick();
private:
    Callback callback;
    uint counter;
    uint step;
};

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

class Amplifier {
public:
    Amplifier();
    u8 Read() const;
    void Write(u8 byte);
    std::tuple<double, double> Amplify(double left, double right) const;
private:
    u8 ctrl;
};

namespace apu {

u8 Digitize(double input);

}

}
