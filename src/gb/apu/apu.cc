#include "apu.h"
#include <array>
#include "bits.h"
#include "log.h"

namespace {

constexpr auto BaseAddress{0xFF24};
constexpr auto BufferSize{1024};

constexpr double ComputeSampleTime(const gb::uint refreshRate) {
    constexpr auto clocksPerSec{4194304.0};
    constexpr auto clocksPerFrame{70224.0};
    constexpr auto sampleTime{1.0 / 44100.0};
    constexpr auto frameRate{clocksPerSec / clocksPerFrame};
    const auto adjustmentFactor{refreshRate / frameRate};
    return sampleTime * adjustmentFactor;
}

}

namespace gb {

Apu_::Apu_(const QueueHandler& queue, const uint refreshRate)
    : queue{queue},
      sampleTime{ComputeSampleTime(refreshRate)},
      enabled{false},
      elapsed{0},
      seq{[this](auto step){SeqTick(step);}} {
    bufferLeft.reserve(BufferSize);
    bufferRight.reserve(BufferSize);
}

Apu Apu_::Create(const QueueHandler& queue, const uint refreshRate) {
    return Apu{new Apu_{queue, refreshRate}};
}

u8 Apu_::Read(const u16 address) const {
    // Wave RAM is always readable.
    if (address >= 0xFF30 && address <= 0xFF3F) {
        return this->ch3.Read(address);
    }

    // Other registers require power on.
    if (!this->enabled && address != (BaseAddress + 2)) {
        return 0xFF;
    }

    // CH1
    if (address >= 0xFF10 && address <= 0xFF14) {
        return this->ch1.Read(address);
    }

    // CH2
    if (address >= 0xFF16 && address <= 0xFF19) {
        return this->ch2.Read(address);
    }

    // CH3
    if (address >= 0xFF1A && address <= 0xFF1E) {
        return this->ch3.Read(address);
    }

    // CH4
    if (address >= 0xFF20 && address <= 0xFF23) {
        return this->ch4.Read(address);
    }

    // Amp
    if (address == BaseAddress) {
        return this->amp.Read();
    }

    // Mixer
    if (address == (BaseAddress + 1)) {
        return this->mixer.Read();
    }

    // Power
    if (address == (BaseAddress + 2)) {
        u8 res{0};
        bit::Update(res, 7, this->enabled);
        bit::Update(res, 3, this->ch1.Active());
        bit::Update(res, 2, this->ch2.Active());
        bit::Update(res, 1, this->ch3.Active());
        bit::Update(res, 0, this->ch4.Active());
        return res;
    }

    log::Warning("APU - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Apu_::Write(const u16 address, const u8 byte) {
    // Wave RAM is always writeable.
    if (address >= 0xFF30 && address <= 0xFF3F) {
        this->ch3.Write(address, byte);
        return;
    }

    // Other registers require power on.
    if (!this->enabled && address != (BaseAddress + 2)) {
        return;
    }

    // CH1
    if (address >= 0xFF10 && address <= 0xFF14) {
        this->ch1.Write(address, byte);
        return;
    }

    // CH2
    if (address >= 0xFF16 && address <= 0xFF19) {
        this->ch2.Write(address, byte);
        return;
    }

    // CH3
    if (address >= 0xFF1A && address <= 0xFF1E) {
        this->ch3.Write(address, byte);
        return;
    }

    // CH4
    if (address >= 0xFF20 && address <= 0xFF23) {
        this->ch4.Write(address, byte);
        return;
    }

    // Amp
    if (address == BaseAddress) {
        this->amp.Write(byte);
        return;
    }

    // Mixer
    if (address == (BaseAddress + 1)) {
        this->mixer.Write(byte);
        return;
    }

    // Power
    if (address == (BaseAddress + 2)) {
        const auto prev{this->enabled};
        const auto next{bit::IsSet(byte, 7)};
        if (prev && !next) {
            Reset();
        }
        this->enabled = next;
        return;
    }

    log::Warning("APU - invalid write address: " + log::Hex(address));
}

void Apu_::Tick(const uint cycles) {
    for (auto i{0u}; i < cycles; ++i) {
        Tick();
    }
}

uint Apu_::SampleCount() const {
    return static_cast<uint>(this->bufferLeft.size());
}

void Apu_::Tick() {
    constexpr auto dt{1.0 / 4194304.0};
    this->elapsed += dt;
    if (this->elapsed > this->sampleTime) {
        this->elapsed -= this->sampleTime;
        Sample();
    }

    if (!this->enabled) return;

    this->seq.Tick();
    this->ch1.Tick();
    this->ch2.Tick();
    this->ch3.Tick();
    this->ch4.Tick();
}

void Apu_::SeqTick(const uint step) {
    bool length{false};
    bool env{false};
    bool sweep{false};
    switch (step) {
        case 0: length = true; break;
        case 2: length = sweep = true; break;
        case 4: length = true; break;
        case 6: length = sweep = true; break;
        case 7: env = true; break;
        default: break;
    }
    if (sweep) this->ch1.SweepTick();
    if (length) {
        this->ch1.LengthTick();
        this->ch2.LengthTick();
        this->ch3.LengthTick();
        this->ch4.LengthTick();
    }
    if (env) {
        this->ch1.EnvTick();
        this->ch2.EnvTick();
        this->ch4.EnvTick();
    }
}

void Apu_::Sample() {
    if (SampleCount() == BufferSize) {
        this->queue(this->bufferLeft, this->bufferRight);
        this->bufferLeft.clear();
        this->bufferRight.clear();
    }

    const auto [l, r] = GetSample();
    this->bufferLeft.push_back(l);
    this->bufferRight.push_back(r);
}

std::tuple<u8, u8> Apu_::GetSample() {
    if (!this->enabled) {
        return {0, 0};
    }
    const auto [lm, rm] = this->mixer.Mix(this->ch1.Out(), this->ch2.Out(),
                                          this->ch3.Out(), this->ch4.Out());
    const auto [la, ra] = this->amp.Amplify(lm, rm);
    const auto [ld, rd] = apu::Digitize(la, ra);
    return {ld, rd};
}

void Apu_::Reset() {
    constexpr std::array<u16, 20> regs {
        0xFF10, 0xFF11, 0xFF12, 0xFF13, 0xFF14,
        0xFF16, 0xFF17, 0xFF18, 0xFF19,
        0xFF1A, 0xFF1B, 0xFF1C, 0xFF1D, 0xFF1E,
        0xFF20, 0xFF21, 0xFF22, 0xFF23,
        0xFF24, 0xFF25
    };
    for (const auto r : regs) {
        Write(r, 0);
    }
    this->seq.Reset();
}

}
