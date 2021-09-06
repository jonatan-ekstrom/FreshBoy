#include "apu.h"
#include "bits.h"
#include "log.h"

namespace {

constexpr auto BaseAddress{0xFF24};
constexpr auto ClocksPerSecond{4194304};
constexpr auto SamplesPerSecond{44100};
constexpr auto BufferSize{1024};

}

namespace gb {

Apu_::Apu_(const QueueHandler& queue, uint)
    : queue{queue},
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

    // Wave RAM
    if (address >= 0xFF30 && address <= 0xFF3F) {
        return this->ch3.Read(address);
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

    // Wave RAM
    if (address >= 0xFF30 && address <= 0xFF3F) {
        this->ch3.Write(address, byte);
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
        this->enabled = bit::IsSet(byte, 7);
        const auto curr{this->enabled};
        if (prev && !curr) {
            Reset();
        }
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
    this->seq.Tick();

    this->ch1.Tick();
    this->ch2.Tick();
    this->ch3.Tick();
    this->ch4.Tick();

    constexpr auto Delta{1.0 / ClocksPerSecond};
    constexpr auto SampleTime{1.0 / SamplesPerSecond};
    this->elapsed += Delta;
    if (this->elapsed > SampleTime) {
        this->elapsed -= SampleTime;
        Sample();
    }
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
    this->seq = Sequencer{[this] (const auto step) { SeqTick(step); }};
    this->ch1 = Sweep{};
    this->ch2 = Tone{};
    this->ch3 = Wave{};
    this->ch4 = Noise{};
    this->mixer = Mixer{};
    this->amp = Amplifier{};
}

}
