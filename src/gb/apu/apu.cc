#include "apu.h"
#include <array>
#include <utility>
#include "bits.h"
#include "display.h"
#include "log.h"

namespace {

/* Number of samples to store before making a call to queue new audio. */
constexpr auto BufferSize{1024};

/* Calculates the number of cycles between each audio sample. */
constexpr double CyclesPerSample(const gb::uint refreshRate, const gb::uint sampleRate) {
    const auto samplesPerSecond{static_cast<double>(sampleRate)};
    const auto cyclesPerSecond{gb::lcd::CyclesPerFrame * refreshRate};
    const auto cyclesPerSample{cyclesPerSecond / samplesPerSecond};
    return cyclesPerSample;
}

}

namespace gb {

Apu_::Apu_(QueueHandler&& queue, const uint refreshRate, const uint sampleRate)
    : queue{std::move(queue)},
      cyclesPerSample{CyclesPerSample(refreshRate, sampleRate)},
      cycles{0},
      enabled{false},
      seq{[this](auto step){SeqTick(step);}} {
    bufferLeft.reserve(BufferSize);
    bufferRight.reserve(BufferSize);
}

Apu Apu_::Create(QueueHandler queue, const uint refreshRate, const uint sampleRate) {
    return Apu{new Apu_{std::move(queue), refreshRate, sampleRate}};
}

u8 Apu_::Read(const u16 address) const {
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
    if (address == 0xFF24) {
        return this->amp.Read();
    }

    // Mixer
    if (address == 0xFF25) {
        return this->mixer.Read();
    }

    // Power
    if (address == 0xFF26) {
        u8 res{0xFF};
        bit::Update(res, 7, this->enabled);
        bit::Update(res, 3, this->ch4.Active());
        bit::Update(res, 2, this->ch3.Active());
        bit::Update(res, 1, this->ch2.Active());
        bit::Update(res, 0, this->ch1.Active());
        return res;
    }

    log::Warning("APU - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Apu_::Write(const u16 address, u8 byte) {
    // Wave RAM is always writeable.
    if (address >= 0xFF30 && address <= 0xFF3F) {
        this->ch3.Write(address, byte);
        return;
    }

    // If power is off, only length counters and NR52 is writeable.
    if (!this->enabled && address != 0xFF11 && address != 0xFF16
                       && address != 0xFF1B && address != 0xFF20
                       && address != 0xFF26) {
        return;
    }

    // If power is off, mask the duty bits.
    if (!this->enabled && (address == 0xFF11 || address == 0xFF16)) {
        byte = static_cast<u8>(byte & 0x3F);
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
    if (address == 0xFF24) {
        this->amp.Write(byte);
        return;
    }

    // Mixer
    if (address == 0xFF25) {
        this->mixer.Write(byte);
        return;
    }

    // Power
    if (address == 0xFF26) {
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

void Apu_::Tick(const uint numCycles) {
    for (auto i{0u}; i < numCycles; ++i) {
        Tick();
    }
}

uint Apu_::SampleCount() const {
    return static_cast<uint>(this->bufferLeft.size());
}

void Apu_::Tick() {
    // Check whether it is time to store a new sample.
    this->cycles += 1;
    if (this->cycles > this->cyclesPerSample) {
        this->cycles -= this->cyclesPerSample;
        Sample();
    }

    // Bail out if power is off.
    if (!this->enabled) return;

    // Step sequencer and all channels.
    this->seq.Tick();
    this->ch1.Tick();
    this->ch2.Tick();
    this->ch3.Tick();
    this->ch4.Tick();
}

void Apu_::SeqTick(const uint step) {
    // Sequencer has fired, determine which units to tick.
    bool length{false}; // Length ticks on steps 0, 2, 4 and 6.
    bool env{false}; // Envelope ticks on step 7.
    bool sweep{false}; // Sweep ticks on step 2 and 6.
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
    // If buffer is full, queue data to audio device before clearing.
    if (SampleCount() == BufferSize) {
        this->queue(this->bufferLeft, this->bufferRight);
        this->bufferLeft.clear();
        this->bufferRight.clear();
    }

    // Store next sample in the buffer.
    const auto [l, r] = GetSample();
    this->bufferLeft.push_back(l);
    this->bufferRight.push_back(r);
}

std::tuple<u8, u8> Apu_::GetSample() {
    if (!this->enabled) {
        return {0, 0};
    }

    // Compute the final sample value by mixing, amplifying and digitizing each channel.
    const auto [lm, rm] = this->mixer.Mix(this->ch1.Out(), this->ch2.Out(),
                                          this->ch3.Out(), this->ch4.Out());
    const auto [la, ra] = this->amp.Amplify(lm, rm);
    const auto [ld, rd] = apu::Digitize(la, ra);
    return {ld, rd};
}

void Apu_::Reset() {
    // These registers are written with zero upon reset.
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
