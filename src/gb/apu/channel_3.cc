#include "channel_3.h"
#include <stdexcept>

namespace {

constexpr auto Nr30Address{0xFF1A};
constexpr auto Nr31Address{0xFF1B};
constexpr auto Nr32Address{0xFF1C};
constexpr auto Nr33Address{0xFF1D};
constexpr auto Nr34Address{0xFF1E};
constexpr auto WaveBase{0xFF30};
constexpr auto WaveTop{0xFF3F};

}

namespace gb {

Channel3::Channel3() : nr30{0}, nr31{0}, nr32{0}, nr33{0}, nr34{0}, wave{} {}

u8 Channel3::Read(const u16 address) const {
    if (address == Nr30Address) {
        return this->nr30 & 0x80;
    }

    if (address == Nr31Address) {
        return this->nr31;
    }

    if (address == Nr32Address) {
        return this->nr32 & 0x60;
    }

    // Nr33 is write-only.

    if (address == Nr34Address) {
        return this->nr34 & 0x40;
    }

    if (address >= WaveBase && address <= WaveTop) {
        return this->wave[address - WaveBase];
    }

    throw std::runtime_error{"Channel3 - invalid read address."};
}

void Channel3::Write(const u16 address, const u8 byte) {
    if (address == Nr30Address) {
        this->nr30 = byte & 0x80;
        return;
    }

    if (address == Nr31Address) {
        this->nr31 = byte;
        return;
    }

    if (address == Nr32Address) {
        this->nr32 = byte & 0x60;
        return;
    }

    if (address == Nr33Address) {
        this->nr33 = byte;
        return;
    }

    if (address == Nr34Address) {
        this->nr34 = byte & 0xC7;
        return;
    }

    if (address >= WaveBase && address <= WaveTop) {
        this->wave[address - WaveBase] = byte;
        return;
    }

    throw std::runtime_error{"Channel3 - invalid write address."};
}

}
