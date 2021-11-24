#include "noise.h"
#include <array>
#include "bits.h"
#include "log.h"

namespace {

constexpr auto BaseAddress{0xFF20};

/* Divisor codes used in frequency computations. */
constexpr std::array<uint, 8> Divisors{8, 16, 32, 48, 64, 80, 96, 112};

}

namespace gb {

Noise::Noise()
    : enabled{false},
      code{0},
      shift{0},
      freq{[this]{Step();}, 8},
      length{[this]{Disable();}, 64} {}

u8 Noise::Read(const u16 address) const {
    if (address == BaseAddress) {
        return 0xFF; // Write-only
    }

    if (address == (BaseAddress + 1)) {
        return this->envelope.Read();
    }

    if (address == (BaseAddress + 2)) {
        auto res{this->code};
        if (this->noise.AltMode()) {
            bit::Set(res, 3);
        }
        res = static_cast<u8>(res | (this->shift << 4));
        return res;
    }

    if (address == (BaseAddress + 3)) {
        const auto le{this->length.Enabled() ? 1 : 0};
        return static_cast<u8>((le << 6) | 0xBF);
    }

    log::Warning("Noise - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Noise::Write(const u16 address, const u8 byte) {
    if (address == BaseAddress) {
        this->length.SetCounter(64 - (byte & 0x3F));
        return;
    }

    if (address == (BaseAddress + 1)) {
        SetDacPower(byte);
        this->envelope.Write(byte);
        return;
    }

    if (address == (BaseAddress + 2)) {
        this->shift = static_cast<u8>((byte >> 4) & 0x0F);
        this->code = static_cast<u8>(byte & 0x07);
        const auto altMode{bit::IsSet(byte, 3)};
        const auto period{Divisors[this->code] << this->shift};
        this->freq.SetPeriod(period);
        this->noise.SetMode(altMode);
        return;
    }

    if (address == (BaseAddress + 3)) {
        this->length.SetEnabled(bit::IsSet(byte, 6));
        if (bit::IsSet(byte, 7)) {
            Trigger();
        }
        return;
    }

    log::Warning("Noise - invalid write address: " + log::Hex(address));
}

bool Noise::Active() const {
    return this->enabled && this->dac.Enabled();
}

double Noise::Out() const {
    if (!this->enabled) return 0;
    return this->dac.Map(this->envelope.Volume(this->noise.Out()));
}

void Noise::Tick() {
    this->freq.Tick();
}

void Noise::LengthTick() {
    this->length.Tick();
}

void Noise::EnvTick() {
    this->envelope.Tick();
}

void Noise::SetDacPower(const u8 byte) {
    this->dac.Enable((byte & 0xF8) != 0);
    if (!this->dac.Enabled()) {
        this->enabled = false;
    }
}

void Noise::Trigger() {
    this->enabled = true;
    this->freq.Trigger();
    this->noise.Trigger();
    this->length.Trigger();
    this->envelope.Trigger();
    if (!this->dac.Enabled()) {
        this->enabled = false;
    }
}

void Noise::Step() {
    this->noise.Tick();
}

void Noise::Disable() {
    this->enabled = false;
}

}
