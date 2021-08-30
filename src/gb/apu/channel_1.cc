#include "channel_1.h"
#include "log.h"

namespace {

constexpr auto Nr10Address{0xFF10};
constexpr auto Nr11Address{0xFF11};
constexpr auto Nr12Address{0xFF12};
constexpr auto Nr13Address{0xFF13};
constexpr auto Nr14Address{0xFF14};

}

namespace gb {

Channel1::Channel1() : nr10{0}, nr11{0}, nr12{0}, nr13{0}, nr14{0} {}

u8 Channel1::Read(const u16 address) const {
    if (address == Nr10Address) {
        return this->nr10;
    }

    if (address == Nr11Address) {
        return this->nr11 & 0xC0;
    }

    if (address == Nr12Address) {
        return this->nr12;
    }

    if (address == Nr13Address) {
        return 0; // Write-only.
    }

    if (address == Nr14Address) {
        return this->nr14 & 0x40;
    }

    log::Warning("Channel 1 - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Channel1::Write(const u16 address, const u8 byte) {
    if (address == Nr10Address) {
        this->nr10 = byte & 0x7F;
        return;
    }

    if (address == Nr11Address) {
        this->nr11 = byte;
        return;
    }

    if (address == Nr12Address) {
        this->nr12 = byte;
        return;
    }

    if (address == Nr13Address) {
        this->nr13 = byte;
        return;
    }

    if (address == Nr14Address) {
        this->nr14 = byte & 0xC7;
        return;
    }

    log::Warning("Channel 1 - invalid write address: " + log::Hex(address));
}

bool Channel1::Enabled() const { return false; }

u8 Channel1::Out() const { return 0; }

}
