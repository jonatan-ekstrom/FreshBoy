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
    u8 Out() const;
    SquareDuty Duty() const;
    void SetDuty(SquareDuty newDuty);
    void Tick();
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
    void Trigger();
    void Tick();
private:
    Callback callback;
    uint period;
    uint counter;
};

class LengthUnit {
public:
    using Callback = std::function<void()>;
    LengthUnit(const Callback& callback, uint period);
    bool Enabled() const;
    void SetEnabled(bool on);
    void SetCounter(uint count);
    void Trigger();
    void Tick();
private:
    Callback callback;
    bool enabled;
    uint period;
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

class SweepUnit {
public:
    using Getter = std::function<u16()>;
    using Setter = std::function<void(u16)>;
    using Disabler = std::function<void()>;
    SweepUnit(const Getter& getter,
              const Setter& setter,
              const Disabler& disabler);
    u8 Read() const;
    void Write(u8 byte);
    void Trigger();
    void Tick();
private:
    u16 Calc() const;
    Getter getter;
    Setter setter;
    Disabler disabler;
    bool enabled;
    uint counter;
    u16 freq;
    u8 data;
};

enum class WaveLevel : u8 {
    Mute = 0,
    Full = 1,
    Half = 2,
    Quarter = 3
};

class WaveUnit {
public:
    WaveUnit();
    u8 Out() const;
    WaveLevel Level() const;
    u8 ReadRam(uint offset) const;
    void WriteRam(uint offset, u8 byte);
    void SetLevel(WaveLevel newLevel);
    void Trigger();
    void Tick();
private:
    std::array<u8, 16> ram;
    WaveLevel level;
    uint pos;
};

class NoiseUnit {
public:
    NoiseUnit();
    u8 Out() const;
    bool AltMode() const;
    void SetMode(bool mode);
    void Trigger();
    void Tick();
private:
    bool altMode;
    u16 reg;
};

class Dac {
public:
    Dac();
    bool Enabled() const;
    double Map(u8 sample) const;
    void Enable(bool on);
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
