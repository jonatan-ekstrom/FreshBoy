#include "tone.h"
#include "bits.h"
#include "log.h"

namespace gb {

ToneBase::ToneBase(const u16 baseAddress)
    : baseAddress{baseAddress},
      enabled{false},
      rawFreq{0},
      freq{[this]{Step();}, 8192},
      length{[this]{Disable();}, 64} {}

u8 ToneBase::Read(const u16 address) const {
    if (address == this->baseAddress) {
        const auto duty{static_cast<u8>(this->square.Duty())};
        return static_cast<u8>(duty << 6);
    }

    if (address == (this->baseAddress + 1)) {
        return this->envelope.Read();
    }

    if (address == (this->baseAddress + 2)) {
        return 0; // Write-only.
    }

    if (address == (this->baseAddress + 3)) {
        const auto le{this->length.Enabled() ? 1 : 0};
        return static_cast<u8>(le << 6);
    }

    log::Warning("ToneBase - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void ToneBase::Write(const u16 address, const u8 byte) {
    if (address == this->baseAddress) {
        this->square.SetDuty(static_cast<SquareDuty>((byte >> 6) & 0x03));
        this->length.SetCounter(byte & 0x3F);
        return;
    }

    if (address == (this->baseAddress + 1)) {
        this->dac.Enable((byte & 0xF8) != 0);
        this->envelope.Write(byte);
        return;
    }

    if (address == (this->baseAddress + 2)) {
        const auto newFreq{static_cast<u16>((this->rawFreq & 0x0700) | byte)};
        SetFrequency(newFreq);
        return;
    }

    if (address == (this->baseAddress + 3)) {
        const auto newFreq{static_cast<u16>((this->rawFreq & 0x00FF) | ((byte & 0x07) << 8))};
        SetFrequency(newFreq);
        this->length.SetEnabled(bit::IsSet(byte, 6));
        if (bit::IsSet(byte, 7)) {
            Trigger();
        }
        return;
    }

    log::Warning("ToneBase - invalid write address: " + log::Hex(address));
}

bool ToneBase::Active() const {
    return this->enabled && this->dac.Enabled();
}

double ToneBase::Out() const {
    if (!this->enabled) return 0;
    return this->dac.Map(this->envelope.Volume(this->square.Out()));
}

void ToneBase::Tick() {
    this->freq.Tick();
}

void ToneBase::LengthTick() {
    this->length.Tick();
}

void ToneBase::EnvTick() {
    this->envelope.Tick();
}

u16 ToneBase::GetFrequency() const { return this->rawFreq; }

void ToneBase::SetFrequency(const u16 newFreq) {
    this->rawFreq = newFreq;
    this->freq.SetPeriod(static_cast<uint>((2048 - this->rawFreq) * 4));
}

void ToneBase::Disable() {
    this->enabled = false;
}

void ToneBase::Trigger() {
    this->enabled = true;
    this->freq.Trigger();
    this->length.Trigger();
    this->envelope.Trigger();
    if (!this->dac.Enabled()) {
        this->enabled = false;
    }
}

void ToneBase::Step() {
    this->square.Tick();
}

Tone::Tone() : ToneBase{0xFF16} {}

}
