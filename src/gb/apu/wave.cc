#include "wave.h"
#include "bits.h"
#include "log.h"

namespace {

constexpr auto BaseAddress{0xFF1A};
constexpr auto WaveBase{0xFF30};
constexpr auto WaveTop{0xFF3F};

}

namespace gb {

Wave::Wave()
    : enabled{false},
      rawFreq{0},
      freq{[this]{Step();}, 4096},
      length{[this]{Disable();}, 256} {}

u8 Wave::Read(const u16 address) const {
    if (address == BaseAddress) {
        const auto bit{this->dac.Enabled() ? 1 : 0};
        return static_cast<u8>(bit << 7);
    }

    if (address == (BaseAddress + 1)) {
        return 0; // Write-only
    }

    if (address == (BaseAddress + 2)) {
        const auto level{static_cast<u8>(this->wave.Level())};
        return static_cast<u8>(level << 5);
    }

    if (address == (BaseAddress + 3)) {
        return 0; // Write-only
    }

    if (address == (BaseAddress + 4)) {
        const auto le{this->length.Enabled() ? 1 : 0};
        return static_cast<u8>(le << 6);
    }

    if (address >= WaveBase && address <= WaveTop) {
        return this->wave.ReadRam(address - WaveBase);
    }

    log::Warning("Wave - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Wave::Write(const u16 address, const u8 byte) {
    if (address == BaseAddress) {
        this->dac.Enable(bit::IsSet(byte, 7));
        return;
    }

    if (address == (BaseAddress + 1)) {
        this->length.SetCounter(256 - byte);
        return;
    }

    if (address == (BaseAddress + 2)) {
        const auto level{static_cast<WaveLevel>((byte >> 5) & 0x03)};
        this->wave.SetLevel(level);
        return;
    }

    if (address == (BaseAddress + 3)) {
        this->rawFreq = static_cast<u16>((this->rawFreq & 0x0700) | byte);
        this->freq.SetPeriod(static_cast<uint>((2048 - this->rawFreq) * 2));
        return;
    }

    if (address == (BaseAddress + 4)) {
        this->rawFreq = static_cast<u16>((this->rawFreq & 0x00FF) | ((byte & 0x07) << 8));
        this->freq.SetPeriod(static_cast<uint>((2048 - this->rawFreq) * 2));
        this->length.SetEnabled(bit::IsSet(byte, 6));
        if (bit::IsSet(byte, 7)) {
            Trigger();
        }
        return;
    }

    if (address >= WaveBase && address <= WaveTop) {
        this->wave.WriteRam(address - WaveBase, byte);
        return;
    }

    log::Warning("Wave - invalid write address: " + log::Hex(address));
}

bool Wave::Active() const {
    return this->enabled && this->dac.Enabled();
}

double Wave::Out() const {
    if (!this->enabled) return 0;
    return this->dac.Map(this->wave.Out());
}

void Wave::Tick() {
    this->freq.Tick();
}

void Wave::LengthTick() {
    this->length.Tick();
}

void Wave::Trigger() {
    this->enabled = true;
    this->freq.Trigger();
    this->length.Trigger();
    this->wave.Trigger();
    if (!this->dac.Enabled()) {
        this->enabled = false;
    }
}

void Wave::Step() {
    this->wave.Tick();
}

void Wave::Disable() {
    this->enabled = false;
}

}
