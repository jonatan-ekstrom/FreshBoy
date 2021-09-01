#include "components.h"
#include "bits.h"

namespace gb {

Sequencer::Sequencer(const Callback& callback)
    : callback{callback}, counter{8192}, step{7} {}

void Sequencer::Tick() {
    if (--this->counter == 0) {
        this->counter = 8192;
        this->step = (this->step + 1) % 8;
        callback(this->step);
    }
}

SquareUnit::SquareUnit()
    : duty{SquareDuty::OneEighth},
      pattern{{{0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 1, 1, 1},
               {0, 1, 1, 1, 1, 1, 1, 0}}},
      pos{0} {}

u8 SquareUnit::Out() const {
    return this->pattern[static_cast<u8>(this->duty)][this->pos];
}

SquareDuty SquareUnit::Duty() const {
    return this->duty;
}

void SquareUnit::SetDuty(const SquareDuty newDuty) {
    this->duty = newDuty;
}

void SquareUnit::Tick() {
    this->pos = (this->pos + 1) % 8;
}

FreqUnit::FreqUnit(const Callback& callback, const uint period)
    : callback{callback},
      period{period},
      counter{period} {}

void FreqUnit::SetPeriod(const uint newPeriod) {
    this->period = newPeriod;
}

void FreqUnit::Trigger() {
    this->counter = this->period;
}

void FreqUnit::Tick() {
    if (--this->counter == 0) {
        this->counter = this->period;
        this->callback();
    }
}

LengthUnit::LengthUnit(const Callback& callback)
    : callback{callback}, enabled{false}, counter{0} {}

bool LengthUnit::Enabled() const {
    return this->enabled;
}

void LengthUnit::SetEnabled(const bool on) {
    this->enabled = on;
}

void LengthUnit::SetCounter(const uint count) {
    this->counter = count;
}

void LengthUnit::Trigger() {
    if (this->counter == 0) {
        this->counter = 64;
    }
}

void LengthUnit::Tick() {
    if (!this->enabled || this->counter == 0) return;
    if (--this->counter == 0) {
        this->callback();
    }
}

EnvelopeUnit::EnvelopeUnit() : data{0}, volume{0}, counter{0} {}

u8 EnvelopeUnit::Volume(const u8 input) const {
    return input * this->volume;
}

u8 EnvelopeUnit::Read() const {
    return this->data;
}

void EnvelopeUnit::Write(const u8 byte) {
    this->data = byte;
}

void EnvelopeUnit::Trigger() {
    this->volume = static_cast<u8>((this->data >> 4) & 0x0F);
    this->counter = this->data & 0x07;
}

void EnvelopeUnit::Tick() {
    if (this->counter == 0) return;
    if (--this->counter == 0) {
        const auto add{(this->data & 0x08) != 0};
        const auto next{this->volume + (add ? 1 : -1)};
        if (next >= 0 && next <= 15) {
            this->volume = static_cast<u8>(next);
            this->counter = this->data & 0x07;
        }
    }
}

Dac::Dac() : enabled{false} {}

bool Dac::Enabled() const {
    return this->enabled;
}

double Dac::Map(const u8 sample) const {
    if (!this->enabled) return 0;
    if (sample >= 15) return 1;
    return sample / 15.0;
}

void Dac::Enable(bool on) {
    this->enabled = on;
}

Mixer::Mixer()
    : mask{0} {}

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

Amplifier::Amplifier()
    : ctrl{0} {}

u8 Amplifier::Read() const {
    return this->ctrl;
}

void Amplifier::Write(const u8 byte) {
    this->ctrl = byte;
}

std::tuple<double, double> Amplifier::Amplify(const double left,
                                              const double right) const {
    const auto leftLevel{static_cast<u8>((this->ctrl >> 4) & 0x07)};
    const auto rightLevel{static_cast<u8>(this->ctrl & 0x07)};

    // Amplify
    double ampLeft{left * (leftLevel + 1)};
    double ampRight{right * (rightLevel + 1)};

    // Normalize
    ampLeft /= 8;
    ampRight /= 8;

    return {ampLeft, ampRight};
}

namespace apu {

u8 Digitize(const double input) {
    const auto digitized{255 * input};
    const auto clampedLow{digitized < 0 ? 0 : digitized};
    const auto clampedHigh{clampedLow > 255 ? 255 : digitized};
    return static_cast<u8>(clampedHigh);
}

}

}
