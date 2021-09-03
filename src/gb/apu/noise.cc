#include "noise.h"
#include "log.h"

namespace {

constexpr auto Nr41Address{0xFF20};
constexpr auto Nr42Address{0xFF21};
constexpr auto Nr43Address{0xFF22};
constexpr auto Nr44Address{0xFF23};

}

namespace gb {

Noise::Noise() : nr41{0}, nr42{0}, nr43{0}, nr44{0} {}

u8 Noise::Read(const u16 address) const {
    if (address == Nr41Address) {
        return this->nr41;
    }

    if (address == Nr42Address) {
        return this->nr42;
    }

    if (address == Nr43Address) {
        return this->nr43;
    }

    if (address == Nr44Address) {
        return this->nr44 & 0x40;
    }

    log::Warning("Channel 4 - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Noise::Write(const u16 address, const u8 byte) {
    if (address == Nr41Address) {
        this->nr41 = byte & 0x3F;
        return;
    }

    if (address == Nr42Address) {
        this->nr42 = byte;
        return;
    }

    if (address == Nr43Address) {
        this->nr43 = byte;
        return;
    }

    if (address == Nr44Address) {
        this->nr44 = byte & 0xC0;
        return;
    }

    log::Warning("Channel 4 - invalid write address: " + log::Hex(address));
}

bool Noise::Active() const { return false; }

double Noise::Out() const { return 0; }

void Noise::Tick() {}

void Noise::LengthTick() {}

void Noise::EnvTick() {}

}
