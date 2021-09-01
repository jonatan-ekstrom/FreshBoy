#include "channel_4.h"
#include "log.h"

namespace {

constexpr auto Nr41Address{0xFF20};
constexpr auto Nr42Address{0xFF21};
constexpr auto Nr43Address{0xFF22};
constexpr auto Nr44Address{0xFF23};

}

namespace gb {

Channel4::Channel4() : nr41{0}, nr42{0}, nr43{0}, nr44{0} {}

u8 Channel4::Read(const u16 address) const {
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

void Channel4::Write(const u16 address, const u8 byte) {
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

bool Channel4::Active() const { return false; }

double Channel4::Out() const { return 0; }

void Channel4::Tick() {}

void Channel4::LengthTick() {}

void Channel4::EnvTick() {}

}
