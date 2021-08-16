#include "sound.h"
#include <stdexcept>

namespace {

constexpr auto Nr50Address{0xFF24};
constexpr auto Nr51Address{0xFF25};
constexpr auto Nr52Address{0xFF26};

}

namespace gb {

Sound::Sound() : ch1{}, ch2{}, ch3{}, ch4{}, nr50{0}, nr51{0}, nr52{0} {}

u8 Sound::Read(const u16 address) const {
    if (address >= 0xFF10 && address <= 0xFF14) {
        return this->ch1.Read(address);
    }

    if (address >= 0xFF16 && address <= 0xFF19) {
        return this->ch2.Read(address);
    }

    if (address >= 0xFF1A && address <= 0xFF1E) {
        return this->ch3.Read(address);
    }

    if (address >= 0xFF30 && address <= 0xFF3F) {
        return this->ch3.Read(address);
    }

    if (address >= 0xFF20 && address <= 0xFF23) {
        return this->ch4.Read(address);
    }

    if (address == Nr50Address) {
        return this->nr50;
    }

    if (address == Nr51Address) {
        return this->nr51;
    }

    if (address == Nr52Address) {
        return this->nr52 & 0x8F;
    }

    throw std::runtime_error{"Sound - invalid read address."};
}

void Sound::Write(const u16 address, const u8 byte) {
    if (address >= 0xFF10 && address <= 0xFF14) {
        this->ch1.Write(address, byte);
        return;
    }

    if (address >= 0xFF16 && address <= 0xFF19) {
        this->ch2.Write(address, byte);
        return;
    }

    if (address >= 0xFF1A && address <= 0xFF1E) {
        this->ch3.Write(address, byte);
        return;
    }

    if (address >= 0xFF30 && address <= 0xFF3F) {
        this->ch3.Write(address, byte);
        return;
    }

    if (address >= 0xFF20 && address <= 0xFF23) {
        this->ch4.Write(address, byte);
        return;
    }

    if (address == Nr50Address) {
        this->nr50 = byte;
        return;
    }

    if (address == Nr51Address) {
        this->nr51 = byte;
        return;
    }

    if (address == Nr52Address) {
        this->nr52 = byte & 0x80;
        return;
    }

    throw std::runtime_error{"Sound - invalid write address."};
}

}
