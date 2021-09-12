#include "components.h"
#include <stdexcept>
#include "bits.h"

namespace {

gb::u8 Digitize(const double input) {
    const auto digitized{255 * input};
    const auto clampedLow{digitized < 0 ? 0 : digitized};
    const auto clampedHigh{clampedLow > 255 ? 255 : digitized};
    return static_cast<gb::u8>(clampedHigh);
}

}

namespace gb {

Sequencer::Sequencer(const Callback& callback)
    : callback{callback}, counter{8192}, step{7} {}

void Sequencer::Tick() {
    if (--this->counter != 0) return;
    this->counter = 8192;
    this->step = (this->step + 1) % 8;
    callback(this->step);
}

void Sequencer::Reset() {
    this->step = 7;
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
    if (this->counter == 0) return;
    if (--this->counter != 0) return;
    this->counter = this->period;
    this->callback();
}

LengthUnit::LengthUnit(const Callback& callback, const uint period)
    : callback{callback}, enabled{false}, period{period}, counter{0} {}

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
        this->counter = period;
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
    if (--this->counter != 0) return;

    const auto add{(this->data & 0x08) != 0};
    const auto next{this->volume + (add ? 1 : -1)};
    if (next >= 0 && next <= 15) {
        this->volume = static_cast<u8>(next);
        this->counter = this->data & 0x07;
    }
}

SweepUnit::SweepUnit(const SweepUnit::Getter& getter,
                     const SweepUnit::Setter& setter,
                     const SweepUnit::Disabler& disabler)
    : getter{getter},
      setter{setter},
      disabler{disabler},
      enabled{false},
      counter{0},
      freq{0},
      data{0} {}

u8 SweepUnit::Read() const {
    return this->data | 0x80;
}

void SweepUnit::Write(const u8 byte) {
    this->data = byte & 0x7F;
}

void SweepUnit::Trigger() {
    const auto period{(this->data >> 4) & 0x07u};
    const auto shift{this->data & 0x07};
    this->freq = this->getter();
    this->counter = period;
    this->enabled = period != 0 || shift != 0;
    if (shift != 0) {
        if (Calc() > 2047) {
            this->disabler();
        }
    }
}

void SweepUnit::Tick() {
    const auto period{(this->data >> 4) & 0x07u};
    if (!this->enabled || period == 0) return;
    if (--this->counter != 0) return;

    const auto newFreq{Calc()};
    if (newFreq > 2047) {
        this->disabler();
        return;
    }

    const auto shift{this->data & 0x07};
    if (shift == 0) return;

    this->freq = newFreq;
    this->setter(newFreq);

    if (Calc() > 2047) {
        this->disabler();
    } else {
        this->counter = period;
    }
}

u16 SweepUnit::Calc() const {
    const auto shift{this->data & 0x07};
    const auto neg{(this->data & 0x08) != 0};
    return static_cast<u16>(this->freq + (neg ? -1 : 1) * (this->freq >> shift));
}

WaveUnit::WaveUnit()
    : ram{},
      level{WaveLevel::Mute},
      pos{0} {}

u8 WaveUnit::Out() const {
    const auto base{pos / 2};
    const auto high{pos % 2 == 0};
    const auto data{high ? bit::HighNibble(this->ram[base]) :
                           bit::LowNibble(this->ram[base])};
    const auto lvl{static_cast<u8>(this->level)};
    const auto shift{lvl == 0 ? 4 : lvl - 1};
    return static_cast<u8>(data >> shift);
}

WaveLevel WaveUnit::Level() const {
    return this->level;
}

u8 WaveUnit::ReadRam(const uint offset) const {
    if (offset > 15) {
        throw std::runtime_error{"WaveUnit - invalid offset."};
    }
    return this->ram[offset];
}

void WaveUnit::WriteRam(const uint offset, const u8 byte) {
    if (offset > 15) {
        throw std::runtime_error{"WaveUnit - invalid offset."};
    }
    this->ram[offset] = byte;
}

void WaveUnit::SetLevel(const WaveLevel newLevel) {
    this->level = newLevel;
}

void WaveUnit::Trigger() {
    this->pos = 0;
}

void WaveUnit::Tick() {
    this->pos = (this->pos + 1) % 32;
}

NoiseUnit::NoiseUnit() : altMode{false}, reg{0x7FFF} {}

u8 NoiseUnit::Out() const {
    return bit::IsSet(this->reg, 0) ? 0 : 1;
}

bool NoiseUnit::AltMode() const {
    return this->altMode;
}

void NoiseUnit::SetMode(const bool mode) {
    this->altMode = mode;
}

void NoiseUnit::Trigger() {
    this->reg = 0x7FFF;
}

void NoiseUnit::Tick() {
    const auto zero{bit::Get(this->reg, 0)};
    const auto one{bit::Get(this->reg, 1)};
    const auto x{(zero ^ one) == 1};
    this->reg = static_cast<u16>(this->reg >> 1);
    bit::Update(this->reg, 14, x);
    if (this->altMode) {
        bit::Update(this->reg, 6, x);
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

std::tuple<u8, u8> Digitize(const double left, const double right) {
    return {::Digitize(left), ::Digitize(right)};
}

}

}
