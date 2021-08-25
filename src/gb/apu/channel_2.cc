#include "channel_2.h"
#include "log.h"

namespace {

constexpr auto Nr21Address{0xFF16};
constexpr auto Nr22Address{0xFF17};
constexpr auto Nr23Address{0xFF18};
constexpr auto Nr24Address{0xFF19};

}

namespace gb {

Channel2::Channel2() : nr21{0}, nr22{0}, nr23{0}, nr24{0} {}

u8 Channel2::Read(const u16 address) const {
    if (address == Nr21Address) {
        return this->nr21 & 0xC0;
    }

    if (address == Nr22Address) {
        return this->nr22;
    }

    if (address == Nr23Address) {
        return 0; // Write-only.
    }

    if (address == Nr24Address) {
        return this->nr24 & 0x40;
    }

    log::Warning("Channel 2 - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Channel2::Write(const u16 address, const u8 byte) {
    if (address == Nr21Address) {
        this->nr21 = byte;
        return;
    }

    if (address == Nr22Address) {
        this->nr22 = byte;
        return;
    }

    if (address == Nr23Address) {
        this->nr23 = byte;
        return;
    }

    if (address == Nr24Address) {
        this->nr24 = byte & 0xC7;
        return;
    }

    log::Warning("Channel 2 - invalid write address: " + log::Hex(address));
}

void Channel2::Reset() {
    this->nr21 = 0;
    this->nr22 = 0;
    this->nr23 = 0;
    this->nr24 = 0;
}

}
