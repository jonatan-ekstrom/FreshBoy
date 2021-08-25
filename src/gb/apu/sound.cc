#include "sound.h"
#include "bits.h"
#include "log.h"

namespace {

constexpr auto Nr50Address{0xFF24};
constexpr auto Nr51Address{0xFF25};
constexpr auto Nr52Address{0xFF26};

}

namespace gb {

Sound_::Sound_() : ch1{}, ch2{}, ch3{}, ch4{}, nr50{0}, nr51{0}, nr52{0} {}

Sound Sound_::Create() { return Sound{new Sound_{}}; }

u8 Sound_::Read(const u16 address) const {
    if (!Enabled() && address != Nr52Address) {
        return 0;
    }

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
        return this->nr52;
    }

    log::Warning("APU - invalid read address: " + log::Hex(address));
    return 0xFF;
}

void Sound_::Write(const u16 address, const u8 byte) {
    if (!Enabled() && address != Nr52Address) {
        return;
    }

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
        Write52(byte);
        return;
    }

    log::Warning("APU - invalid write address: " + log::Hex(address));
}

void Sound_::Write52(const u8 byte) {
    const u8 mask{0x80};
    bit::Assign(this->nr52, byte, mask);
    if (!Enabled()) {
        Reset();
    }
}

bool Sound_::Enabled() const {
    return bit::IsSet(this->nr52, 7);
}

void Sound_::Reset() {
    this->ch1.Reset();
    this->ch2.Reset();
    this->ch3.Reset();
    this->ch4.Reset();
    this->nr50 = 0;
    this->nr51 = 0;
    this->nr52 = 0;
}

}
