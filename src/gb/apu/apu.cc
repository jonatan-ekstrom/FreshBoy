#include "apu.h"
#include "bits.h"
#include "log.h"

namespace {

constexpr auto Nr50Address{0xFF24};
constexpr auto Nr51Address{0xFF25};
constexpr auto Nr52Address{0xFF26};
constexpr auto ClocksPerSecond{4194304};
constexpr auto SamplesPerSecond{44100};
constexpr auto Delta{1.0 / ClocksPerSecond};
constexpr auto SampleTime{1.0 / SamplesPerSecond};

}

namespace gb {

Apu_::Apu_() : enabled{false}, elapsed{0}, seq{[this] (const auto step) { SeqTick(step); }} {
    constexpr auto frameSize{SamplesPerSecond / 60};
    constexpr auto bufSize{2 * frameSize};
    bufferLeft.reserve(bufSize);
    bufferRight.reserve(bufSize);
}

Apu Apu_::Create() { return Apu{new Apu_{}}; }

u8 Apu_::Read(const u16 address) const {
    if (!this->enabled && address != Nr52Address) {
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
    if (address == Nr50Address) {
        return this->amp.Read();
    }

    // Mixer
    if (address == Nr51Address) {
        return this->mixer.Read();
    }

    // Power
    if (address == Nr52Address) {
        u8 res{0};
        bit::Update(res, 7, this->enabled);
        bit::Update(res, 3, this->ch1.Enabled());
        bit::Update(res, 2, this->ch2.Enabled());
        bit::Update(res, 1, this->ch3.Enabled());
        bit::Update(res, 0, this->ch4.Enabled());
        return res;
    }

    log::Warning("APU - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Apu_::Write(const u16 address, const u8 byte) {
    if (!this->enabled && address != Nr52Address) {
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
    if (address == Nr50Address) {
        this->amp.Write(byte);
        return;
    }

    // Mixer
    if (address == Nr51Address) {
        this->mixer.Write(byte);
        return;
    }

    // Power
    if (address == Nr52Address) {
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

const Apu_::Samples& Apu_::LeftChannel() const { return this->bufferLeft; }

const Apu_::Samples& Apu_::RightChannel() const { return this->bufferRight; }

void Apu_::ClearSamples() {
    this->bufferLeft.clear();
    this->bufferRight.clear();
}

void Apu_::Tick() {
    this->seq.Tick();

    this->ch1.Tick();
    this->ch2.Tick();
    this->ch3.Tick();
    this->ch4.Tick();

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
    if (!this->enabled) {
        this->bufferLeft.push_back(0);
        this->bufferRight.push_back(0);
        return;
    }
    const auto [lm, rm] = this->mixer.Mix(this->ch1.Out(), this->ch2.Out(),
                                          this->ch3.Out(), this->ch4.Out());
    const auto [la, ra] = this->amp.Amplify(lm, rm);
    this->bufferLeft.push_back(apu::Digitize(la));
    this->bufferRight.push_back(apu::Digitize(ra));
}

void Apu_::Reset() {
    this->seq = Sequencer{[this] (const auto step) { SeqTick(step); }};
    this->ch1 = Channel1{};
    this->ch2 = Channel2{};
    this->ch3 = Channel3{};
    this->ch4 = Channel4{};
    this->mixer = Mixer{};
    this->amp = Amplifier{};
}

}
