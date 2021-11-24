#pragma once
#include <array>
#include <functional>
#include <tuple>
#include "types.h"

namespace gb {

/* List of component helper classes used by the different audio channels. */

/* Top level sequencer unit. */
class Sequencer {
public:
    /* Callback function called on each new sequence step. */
    using Callback = std::function<void(uint)>;

    /* Constructs a new sequencer and registers the provided callback. */
    explicit Sequencer(const Callback& callback);

    /* Ticks the sequencer one machine cycle. */
    void Tick();

    /* Resets the sequencer to its initial state. */
    void Reset();
private:
    Callback callback;
    uint counter;
    uint step;
};

/* Enumeration of the different square wave duty cycles. */
enum class SquareDuty : u8 {
    OneEighth = 0,
    Quarter = 1,
    Half = 2,
    ThreeQuarters = 3
};

/* Square wave generator. */
class SquareUnit {
public:
    /* Constructs a new square wave generator. */
    SquareUnit();

    /* Retrieves current output level. */
    u8 Out() const;

    /* Returns the currently used duty cycle. */
    SquareDuty Duty() const;

    /* Changes the duty cycle. */
    void SetDuty(SquareDuty newDuty);

    /* Advances the square wave one step in the duty cycle. */
    void Tick();
private:
    SquareDuty duty;
    std::array<std::array<u8, 8>, 4> pattern;
    uint pos;
};

/* Frequency generator. */
class FreqUnit {
public:
    /* Callback function called when the timer expires. */
    using Callback = std::function<void()>;

    /* Constructs a new frequency unit, registering the provided callback and sets the initial period. */
    FreqUnit(const Callback& callback, uint period);

    /* Updates the period. */
    void SetPeriod(uint newPeriod);

    /* Resets timer counter to the current period. */
    void Trigger();

    /* Ticks the counter one step. */
    void Tick();
private:
    Callback callback;
    uint period;
    uint counter;
};

/* Effect length, timer component. */
class LengthUnit {
public:
    /* Callback function, called when the timer expires. */
    using Callback = std::function<void()>;

    /* Creates a new length unit, registering the provided callback and sets the period. */
    LengthUnit(const Callback& callback, uint period);

    /* Returns true if the component is enabled. */
    bool Enabled() const;

    /* Enables, or disables the component. */
    void SetEnabled(bool on);

    /* Sets the length counter (timer period). */
    void SetCounter(uint count);

    /* Triggers a new sound effect. */
    void Trigger();

    /* Steps the length unit counter. */
    void Tick();
private:
    Callback callback;
    bool enabled;
    uint period;
    uint counter;
};

/* Volume envelope unit. */
class EnvelopeUnit {
public:
    /* Creates a new envelope unit. */
    EnvelopeUnit();

    /* Sets the current input volume */
    u8 Volume(u8 input) const;

    /* Reads the envelope unit I/O register. */
    u8 Read() const;

    /* Writes to the envelope unit I/O register. */
    void Write(u8 byte);

    /* Triggers a volume envelope. */
    void Trigger();

    /* Steps the envelope (volume) level. */
    void Tick();
private:
    u8 data;
    u8 volume;
    uint counter;
};

/* Frequency sweep component. */
class SweepUnit {
public:
    /* Callback function for retrieving the current frequency. */
    using Getter = std::function<u16()>;

    /* Callback function for setting a new frequency. */
    using Setter = std::function<void(u16)>;

    /* Callback function for disabling the channel. */
    using Disabler = std::function<void()>;

    /* Constructs a new sweep unit and registers the provided callbacks. */
    SweepUnit(const Getter& getter, const Setter& setter, const Disabler& disabler);

    /* Reads the internal I/O register. */
    u8 Read() const;

    /* Writes to the internal I/O register. */
    void Write(u8 byte);

    /* Triggers the start of a new frequency sweep. */
    void Trigger();

    /* Advances the state of the sweep unit. */
    void Tick();
private:
    u16 Calc();
    void Calc(bool update);
    bool ReloadCounter();
    Getter getter;
    Setter setter;
    Disabler disabler;
    bool enabled;
    bool negUsed;
    uint counter;
    u16 freq;
    u8 data;
};

/* Enumeration of supported volume levels for the wave unit. */
enum class WaveLevel : u8 {
    Mute = 0,
    Full = 1,
    Half = 2,
    Quarter = 3
};

/* Wave unit (arbitrary waveform generator). */
class WaveUnit {
public:
    /* Creates a new wave unit. */
    WaveUnit();

    /* Reads the internal I/O register. */
    u8 Out() const;

    /* Returns the current wave level (volume). */
    WaveLevel Level() const;

    /* Read one byte from wave RAM at the provided offset. */
    u8 ReadRam(uint offset) const;

    /* Write one byte of wave RAM at the provided offset. */
    void WriteRam(uint offset, u8 byte);

    /* Set a new wave level. */
    void SetLevel(WaveLevel newLevel);

    /* Trigger playback of the waveform. */
    void Trigger();

    /* Advance the waveform position one step. */
    void Tick();
private:
    std::array<u8, 16> ram;
    WaveLevel level;
    uint pos;
};

/* Pseudo-random noise generator. */
class NoiseUnit {
public:
    /* Creates a new noise unit. */
    NoiseUnit();

    /* Reads the internal I/O register. */
    u8 Out() const;

    /* Checks whether alternative mode is enabled. */
    bool AltMode() const;

    /* Enables / disables alternative mode. */
    void SetMode(bool mode);

    /* Triggers playback of a new noise effect. */
    void Trigger();

    /* Advances the state of the PRNG. */
    void Tick();
private:
    bool altMode;
    u16 reg;
};

/* Digital to analog converter component. */
class Dac {
public:
    /* Creates a new DAC. */
    Dac();

    /* Returns true if the DAC is enabled. */
    bool Enabled() const;

    /* Maps a new digital sample to an analogue output value. */
    double Map(u8 sample) const;

    /* Enables / disables the DAC. */
    void Enable(bool on);
private:
    bool enabled;
};

/* Component used to mix the four channels together. */
class Mixer {
public:
    /* Creates a new mixer. */
    Mixer();

    /* Reads the I/O register. */
    u8 Read() const;

    /* Writes to the I/O register. */
    void Write(u8 byte);

    /* Mixes the four channels into a left and right sample value. */
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

/* Digitizes left / right analogue values into a digital sample. */
std::tuple<u8, u8> Digitize(double left, double right);

}

}
