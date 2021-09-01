#include "channel_2.h"
#include "bits.h"
#include "log.h"

namespace {

constexpr auto Nr21Address{0xFF16};
constexpr auto Nr22Address{0xFF17};
constexpr auto Nr23Address{0xFF18};
constexpr auto Nr24Address{0xFF19};

}

namespace gb {

Channel2::Channel2()
    : freq{[this]{Step();}, 8192},
      length{[this]{Disable();}},
      enabled{false},
      rawFreq{0} {}

u8 Channel2::Read(const u16 address) const {
    if (address == Nr21Address) {
        const auto duty{static_cast<u8>(this->square.Duty())};
        return static_cast<u8>(duty << 6);
    }

    if (address == Nr22Address) {
        return this->envelope.Read();
    }

    if (address == Nr23Address) {
        return 0; // Write-only.
    }

    if (address == Nr24Address) {
        const auto le{this->length.Enabled() ? 1 : 0};
        return static_cast<u8>(le << 6);
    }

    log::Warning("Channel 2 - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Channel2::Write(const u16 address, const u8 byte) {
    if (address == Nr21Address) {
        this->square.SetDuty(static_cast<SquareDuty>((byte >> 6) & 0x03));
        this->length.SetCounter(byte & 0x3F);
        return;
    }

    if (address == Nr22Address) {
        this->dac.Enable((byte & 0xF8) != 0);
        this->envelope.Write(byte);
        return;
    }

    if (address == Nr23Address) {
        this->rawFreq = static_cast<u16>((this->rawFreq & 0x0700) | byte);
        this->freq.SetPeriod(static_cast<uint>((2048 - this->rawFreq) * 4));
        return;
    }

    if (address == Nr24Address) {
        this->rawFreq = static_cast<u16>((this->rawFreq & 0x00FF) | ((byte & 0x07) << 8));
        this->freq.SetPeriod(static_cast<uint>((2048 - this->rawFreq) * 4));
        this->length.SetEnabled(bit::IsSet(byte, 6));
        if (bit::IsSet(byte, 7)) {
            Trigger();
        }
        return;
    }

    log::Warning("Channel 2 - invalid write address: " + log::Hex(address));
}

bool Channel2::Active() const {
    return this->enabled && this->dac.Enabled();
}

double Channel2::Out() const {
    if (!this->enabled) return 0;
    return this->dac.Map(this->envelope.Volume(this->square.Out()));
}

void Channel2::Tick() {
    this->freq.Tick();
}

void Channel2::LengthTick() {
    this->length.Tick();
}

void Channel2::EnvTick() {
    this->envelope.Tick();
}

void Channel2::Trigger() {
    this->enabled = true;
    this->freq.Trigger();
    this->length.Trigger();
    this->envelope.Trigger();
    if (!this->dac.Enabled()) {
        this->enabled = false;
    }
}

void Channel2::Step() {
    this->square.Tick();
}

void Channel2::Disable() {
    this->enabled = false;
}

}
