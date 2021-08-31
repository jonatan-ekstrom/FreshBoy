#pragma once
#include <array>
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

enum class SquareDuty : u8 {
    OneEighth = 0,
    Quarter = 1,
    Half = 2,
    ThreeQuarters = 3
};

class SquareUnit {
public:
    SquareUnit();
    void Tick();
    u8 Out() const;
    void SetDuty(SquareDuty newDuty);
private:
    SquareDuty duty;
    std::array<std::array<u8, 8>, 4> pattern;
    uint pos;
};

class FreqUnit {
public:
    using Callback = std::function<void()>;
    FreqUnit(const Callback& callback, uint period);
    void SetPeriod(uint newPeriod);
    void Tick();
private:
    Callback callback;
    uint period;
    uint counter;
};

class LengthUnit {
public:
    using Callback = std::function<void()>;
    explicit LengthUnit(const Callback& callback);
    bool Enabled() const;
    void SetEnabled(bool on);
    void SetCounter(uint count);
    void Trigger();
    void Tick();
private:
    Callback callback;
    bool enabled;
    uint counter;
};

class EnvelopeUnit {
public:
    EnvelopeUnit();
    u8 Volume(u8 input) const;
    u8 Read() const;
    void Write(u8 byte);
    void Trigger();
    void Tick();
private:
    u8 data;
    u8 volume;
    uint counter;
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
